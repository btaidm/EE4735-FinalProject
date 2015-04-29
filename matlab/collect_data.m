clc
clear

file = 'calibrate-echos-2.mat';

fprintf('Waiting for Start string of %s\n',file)

% Open Serial Port for Data gathering
bot = serial('/dev/ttyACM0');

fopen(bot);

inString = '';

% Wait for the all clear
while(~strcmp(inString,'STARTCOL'))
    inString = '';
    if(bot.BytesAvailable >= 8)
        captureBytes = fread(bot, 8, 'char');
        inString = char(captureBytes');
    end
end

fprintf('Starting Collection\n')
tic
left = 1:1000;
right = 1:1000;
distance = 1:1000;
for i = 1:length(left)
    distanceValues = fread(bot, 3, 'uint32');
    left(i) = distanceValues(1);
    right(i) = distanceValues(2);
    distance(i) = distanceValues(3);
end
toc
fprintf('Done Collecting Data\n')

fclose(bot)
delete(bot)
clear bot

save(file,'left', 'right', 'distance');