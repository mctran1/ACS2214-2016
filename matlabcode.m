   delete(instrfindall);
  clear all; clc; close all;
% Initialize serial port
s = serial('COM1','BaudRate',9600);   
%set(s, ' Terminator', 'LF'); % Default terminator is \n
set(s,'BaudRate', 9600);
set(s,'DataBits', 8);
set(s,'StopBits', 1);
fopen(s);

% variables
numberOfData = 50;

i = 1;
% Main graph figure

% Start asynchronous reading
% readasync(s);
while(i<=numberOfData)  
      % Get the data from the serial object
      data(i) =  fscanf(s, '%f');
      data1(i) = fscanf(s, '%f');
      data2(i) = fscanf(s, '%f');

      
     data(i), data1(i), data2(i)
end

fclose (s);
delete(s);
