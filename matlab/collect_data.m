clc
clear

file = '300cm-narrow-open.mat';
% finishup = onCleanup(@() clean);

fprintf('Waiting for Start string of %s\n',file)

bot = serial('/dev/ttyACM0');

s.BytesAvailableFcnCount = 8;
s.BytesAvailableFcnMode = 'byte';
s.BytesAvailableFcn = @instrcallback;

fopen(bot);

inString = '';

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
for i = 1:length(left)
    distanceValues = fread(bot, 2, 'uint32');
    left(i) = distanceValues(1);
    right(i) = distanceValues(2);
end
toc
fprintf('Done Collecting Data\n')

fclose(bot)
delete(bot)
clear bot

save(file,'left', 'right');