clc;
clear all;
close all;

ki=1;
kp=1;
g=9.81;
L=2.6;
lr=0.5;
lf=2.1;
h=0.25;
m=180;
ls=1.242;
rw=0.217;
drive_ratio=10;
A=0;
% Otwórz model
open_system('tv');

% Pobierz aktualny zestaw konfiguracji
cs = getActiveConfigSet('tv');

set_param(cs, 'BlockReduction', 'off'); % Wyłączenie redukcji bloków
set_param(cs, 'InlineParams', 'off'); % Wyłączenie inliningu parametrów


% Zapisz zmiany
save_system('tv');



