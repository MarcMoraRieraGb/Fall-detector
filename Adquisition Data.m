clear all
close all
clc;
contador=1;

num_muestras=300;
% temps = clock;
% fix(temps);
delete(instrfind({'Port'},{'COM11'}));
puerto=serial('COM11');
puerto.BaudRate=115200;
warning('off', 'MATLAB:serial:fscanf:unsuccessfulRead');

disp('Connectant')
fopen(puerto);
% temps2 = clock;
% fix(temps2);
disp('Estem Connectats')

while (contador<=num_muestras)

    llegir=fscanf(puerto, '%s');
    valor=split(llegir, '/t');
    yaw(contador)=str2double(valor(1));
    pitch(contador)=str2double(valor(2));
    roll(contador)=str2double(valor(3));
    q_x(contador)=str2double(valor(4));
    q_y(contador)=str2double(valor(5));
    q_z(contador)=str2double(valor(6));
    q_w(contador)=str2double(valor(7));
    Acc_x_RAW(contador)=str2double(valor(8));
    Acc_y_RAW(contador)=str2double(valor(9));
    Acc_z_RAW(contador)=str2double(valor(10));
    Rot_x(contador)=str2double(valor(11));
    Rot_y(contador)=str2double(valor(12));
    Rot_z(contador)=str2double(valor(13));
    mostra(contador)=str2double(valor(14));
    contador=contador+1;
disp(contador)
%     if (contador==2)
%         temps3 = clock;
%         fix(temps3);
%     end
%         if (contador==12)
%         temps4 = clock;
%         fix(temps4);
%     end
        
end
% temps5 = clock;
% fix(temps5);

disp('Acabat')

fclose(puerto);
delete(puerto);

for i=1:300
    mostras(i)=i;
end
Acc_x =Acc_x_RAW * (9.81/16384.0);
Acc_y=Acc_y_RAW * (9.81/16384.0);
Acc_z =Acc_z_RAW * (9.81/16384.0);

figure('Name', 'Acceleració en x')
plot (mostras, Acc_x);
ylabel('Acceleració (m/s2)')
xlabel('Mostres')
% mitjaAX=mean(Acc_x);


figure('Name', 'Acceleració en y')
plot (mostras, Acc_y);
ylabel('Acceleració (m/s2)')
xlabel('Mostres')
% mitjaAY=mean(Acc_y);

figure('Name', 'Acceleració en z')
plot (mostras, Acc_z);
ylabel('Acceleració (m/s2)')
xlabel('Mostres')
% mitjaAZ=mean(Acc_z);
% 
% figure('Name', 'Rotació en x')
% plot (mostras, Rot_x);
% ylabel('Acceleració (raw)')
% xlabel('Mostres')
% mitjaRX=mean(Rot_x);
% 
% figure('Name', 'Rotació en y')
% plot (mostras, Rot_y);
% ylabel('Acceleració (raw)')
% xlabel('Mostres')
% mitjaRY=mean(Rot_y);
% 
% 
% figure('Name', 'Rotació en z')
% plot (mostras, Rot_z);
% ylabel('Acceleració (raw)')
% xlabel('Mostres')
% mitjaRZ=mean(Rot_z);
% 
% % x=mostras(:).';
% % y=Acc_x(:).';
% %  
% % mdl = stepwiseglm(x,y)
% % plot (mdl)
