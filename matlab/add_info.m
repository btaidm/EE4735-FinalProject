files = dir('*.mat')

for file = files'
    fprintf('Adding information for %s.\n',file.name)

    wide = input('Is object in wide position? [1/0]: ');
    hallway = input('Is object in a hallway type setting? [1/0]: ');
    distance = input('Object Distance [cm]: ');

    save(file.name,'wide','hallway','distance', '-append');
end
