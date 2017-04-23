clear all;
close all;


%% Test Points 
Initial_Point = [-11.6300;  303.0700;  258.4100]
Test_Points = [Initial_Point + [0; 100; 0], Initial_Point + [-100; 100; 100], Initial_Point + [-100; 0; 100], Initial_Point];

%% Load Data
File_Name = 'PositionLog.txt';
Data = dlmread(File_Name);

%% Plot

%plot the test points first
Marker_Size = 100;
Line_Width = 2;

figure;
scatter3(Initial_Point(1), Initial_Point(2), Initial_Point(3), Marker_Size*1.1, [1 0 0],'filled' );
hold on;
scatter3(Test_Points(1,:), Test_Points(2,:), Test_Points(3,:),Marker_Size, [0 1 0], 'filled');
hold on;

%plot the movement
plot3(Data(:,1),Data(:,2),Data(:,3), 'LineWidth', Line_Width)
hold on;

%refine plot
view([42,26]);
grid on;
xlabel('X Axis [mm]')
ylabel('Y Axis [mm]')
zlabel('Z Axis [mm]')
legend('Initial Position', 'Test Points', 'Trajectory')

Offsett = 5;
Font = 10;
text(Test_Points(1,1) + Offsett, Test_Points(2,1) + Offsett, Test_Points(3,1), 'P1', 'FontSize',Font, 'FontWeight', 'bold');
text(Test_Points(1,2) + Offsett, Test_Points(2,2) + Offsett, Test_Points(3,2), 'P2', 'FontSize',Font, 'FontWeight', 'bold');
text(Test_Points(1,3) , Test_Points(2,3) - Offsett*4, Test_Points(3,3), 'P3', 'FontSize',Font, 'FontWeight', 'bold');