fclose(instrfind)
delete(instrfind)
clc
clear

clockspeed = 1.1 * 10^6; % Hz
soundSpeed = 343.59; % m/s

% finishup = onCleanup(@() clean);

fprintf('Waiting for Start string\n')

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

left = zeros(1,1000);
right = zeros(1,1000);
count = 0;

while(1)
    distanceValues = double(swapbytes(uint32(fread(bot, 2, 'uint32'))));
    left(mod(count,1000)+1) = distanceValues(1);
    right(mod(count,1000)+1) = distanceValues(2);


    % Raw
    % figure(1)
    % clf;
    % hold on
    % plot(right, '-')
    % plot(left, '-')
    % hold off
    % legend('Right Pinger', 'Left Pinger')
    % title(['Raw Pinger Data'])
    % xlabel('Pinger Iteration')
    % ylabel('Cycles')

    % % Seconds
    % figure(2)
    % clf;
    % hold on
    % rightT = right / clockspeed;
    % leftT = left / clockspeed;
    % plot(rightT * 1000, '-')
    % plot(leftT * 1000, '-')
    % hold off
    % legend('Right Pinger', 'Left Pinger')
    % title(['Timed Pinger Data'])
    % xlabel('Pinger Iteration')
    % ylabel('Time (ms)')


    % % Distance
    % figure(3)
    % clf;
    % hold on
    % rightD = rightT * 1000000 / 58;
    % leftD = leftT * 1000000 / 58;
    % plot(rightD, '-')
    % plot(leftD, '-')
    % hold off
    % legend('Right Pinger', 'Left Pinger')
    % title(['Distance Pinger Data'])
    % xlabel('Pinger Iteration')
    % ylabel('Distance (cm)')
    %axis([1 1000 0 3])

    % Cycles to Distance
    set(0,'CurrentFigure',4);
    clf;
    hold on
    rightCD = uint32(uint32(right)/uint32(64));
    leftCD = uint32(uint32(left)/uint32(64));
    plot(1:(mod(count,1000)+1), rightCD(1:(mod(count,1000)+1)), '-')
    plot(1:(mod(count,1000)+1),leftCD(1:(mod(count,1000)+1)), '-')
    hold off
    legend('Right Pinger', 'Left Pinger')
    title(['Cycle to Distance Pinger Data'])
    xlabel('Pinger Iteration')
    ylabel('Distance (cm)')
    count = count + 1;
    if(mod(count, 10) == 0)
        drawnow update;
    end
end
