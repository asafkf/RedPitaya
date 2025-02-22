%% Define Red Pitaya as TCP/IP object
clc
clear all
close all
IP= '';           % Input IP of your Red Pitaya...
port = 5000;                    % If you are using WiFi then IP is:              
tcpipObj=tcpip(IP, port);      

fopen(tcpipObj);
tcpipObj.Terminator = 'CR/LF';

%% The example generate sine bursts every 0.5 seconds indefinety
%fprintf(tcpipObj,'GEN:RST');               % Reset generator

fprintf(tcpipObj,'SOUR1:FUNC SINE');                                                 
fprintf(tcpipObj,'SOUR1:FREQ:FIX 1000');    % Set frequency of output signal
fprintf(tcpipObj,'SOUR1:VOLT 1');           % Set amplitude of output signal

fprintf(tcpipObj,'SOUR1:BURS:STAT BURST');  % Set burst mode to ON
fprintf(tcpipObj,'SOUR1:BURS:NCYC 1');      % Set 1 pulses of sine wave
fprintf(tcpipObj,'SOUR1:BURS:NOR 10000');   % Infinity number of sine wave pulses
fprintf(tcpipObj,'SOUR1:BURS:INT:PER 5000');% Set time of burst period in microseconds = 5 * 1/Frequency * 1000000

fprintf(tcpipObj,'OUTPUT1:STATE ON');       % Set output to ON
fprintf(tcpipObj,'SOUR1:TRIG:INT');         % Set generator trigger to immediately

%% Close connection with Red Pitaya

fclose(tcpipObj);
