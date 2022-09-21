"""SCPI access to Red Pitaya."""

import socket
import typing

__author__ = "Luka Golinar, Iztok Jeras"
__copyright__ = "Copyright 2015, Red Pitaya"


class SCPI:
    """SCPI class used to access Red Pitaya over an IP network."""

    delimiter = "\r\n"  # CRLF

    def __init__(self, host: str, timeout: typing.Optional[float] = None, port: int = 5000) -> None:
        """Initialize object and open IP connection.
        Host IP should be a string in parentheses, like '192.168.1.100'.
        """
        self._host = host
        self._port = port
        self._timeout = timeout

        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            if timeout is not None:
                self._socket.settimeout(timeout)
            self._socket.connect((host, port))
        except socket.error as error:
            raise socket.error(f"SCPI >> connect({host!s}:{port:d}) failed: {error!s}") from error

    def __del__(self) -> None:
        self._socket.close()

    def close(self) -> None:
        """Close IP connection."""
        self._socket.close()

    def rx_txt(self, chunk_size: int = 4096) -> str:
        """Receive text string and return it after removing the delimiter."""
        msg = ""
        while True:
            chunk = self._socket.recv(chunk_size).decode("utf-8")  # Receive chunk size of 2^n preferably
            msg += chunk
            if len(msg) and (msg[-2:] == self.delimiter):
                break
        return msg[:-2]

    def rx_arb(self) -> typing.Union[typing.Literal[False], bytes]:
        """Receive binary data from scpi server"""
        received_bytes = b""
        while len(received_bytes) != 1:
            received_bytes = self._socket.recv(1)
        if received_bytes != b"#":
            return False
        received_bytes = b""
        while len(received_bytes) != 1:
            received_bytes = self._socket.recv(1)
        num_of_num_bytes = int(received_bytes)
        if num_of_num_bytes <= 0:
            return False
        received_bytes = b""
        while len(received_bytes) != num_of_num_bytes:
            received_bytes += self._socket.recv(1)
        num_of_bytes = int(received_bytes)
        received_bytes = b""
        while len(received_bytes) != num_of_bytes:
            received_bytes += self._socket.recv(4096)
        return received_bytes

    def tx_txt(self, msg: str) -> None:
        """Send text string ending and append delimiter."""
        return self._socket.sendall((msg + self.delimiter).encode("utf-8"))  # was send(().encode('utf-8'))

    def txrx_txt(self, msg: str) -> str:
        """Send/receive text string."""
        self.tx_txt(msg)
        return self.rx_txt()

    # IEEE Mandated Commands

    def cls(self) -> None:
        """Clear Status Command"""
        return self.tx_txt("*CLS")

    def ese(self, value: int) -> None:
        """Standard Event Status Enable Command"""
        return self.tx_txt(f"*ESE {value}")

    def ese_q(self) -> str:
        """Standard Event Status Enable Query"""
        return self.txrx_txt("*ESE?")

    def esr_q(self) -> str:
        """Standard Event Status Register Query"""
        return self.txrx_txt("*ESR?")

    def idn_q(self) -> str:
        """Identification Query"""
        return self.txrx_txt("*IDN?")

    def opc(self) -> None:
        """Operation Complete Command"""
        return self.tx_txt("*OPC")

    def opc_q(self) -> str:
        """Operation Complete Query"""
        return self.txrx_txt("*OPC?")

    def rst(self) -> None:
        """Reset Command"""
        return self.tx_txt("*RST")

    def sre(self) -> None:
        """Service Request Enable Command"""
        return self.tx_txt("*SRE")

    def sre_q(self) -> str:
        """Service Request Enable Query"""
        return self.txrx_txt("*SRE?")

    def stb_q(self) -> str:
        """Read Status Byte Query"""
        return self.txrx_txt("*STB?")

    # :SYSTEM

    def err_c(self) -> str:
        """Error count."""
        return self.txrx_txt("SYST:ERR:COUN?")

    def err_n(self) -> str:
        """Error next."""
        return self.txrx_txt("SYST:ERR:NEXT?")
