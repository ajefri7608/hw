function [hiddenmatrix,iter,hiddensigma,input]=EBPTA3

load IRIS_IN.csv;
load IRIS_OUT.csv;
input = IRIS_IN;
target = IRIS_OUT;
out=[]
outnet=[];



% initialize the weight matrix
outputmatrix=zeros(12,1);
for i=1:1:12
 for j=1:1:1
   outputmatrix(i,j)=rand;
 end
end

hiddenmatrix=zeros(4,12);
for i=1:1:4
 for j=1:1:12
   hiddenmatrix(i,j)=rand;
 end
end


RMSE1=zeros(100,1);
RMSE2=zeros(100,1);


% Training
for epoch=1:1:100
t1=[];
t2=[];
for iter=1:1:75

% forward �e�ǳ���

% training
hiddensigma=input(iter,:)*hiddenmatrix;
hiddennet=logsig(hiddensigma);       

outputsigma=hiddennet*outputmatrix;
outputnet=purelin(outputsigma);    


% simalation 
if iter+75<=length(input) % take the first 400 as training samples, the remaining 200 as simulations
hsigma=input(iter+75,:)*hiddenmatrix;
hnet=logsig(hsigma);       

osigma=hnet*outputmatrix;
onet=purelin(osigma);

mis=target(iter+75)-onet;
t2=[t2;mis.^2];
end





% backward part �˶ǳ���
% delta of outputmatrix ��X�h�� delta
doutputnet=dpurelin(outputsigma);
deltaoutput=(target(iter)-outputnet)*doutputnet;
error=target(iter)-outputnet;
t1=[t1;error.^2];


% delta of hidden layer ���üh�� delta
tempdelta=deltaoutput*outputmatrix;
transfer=dlogsig(hiddensigma,logsig(hiddensigma));
deltahidden=[];
for i=1:1:12
deltahidden=[deltahidden;tempdelta(i)*transfer(i)];
end

% output layer weight update ��X�h�v����s
newoutputmatrix=outputmatrix+0.025*(deltaoutput*hiddennet)';
outputmatrix=newoutputmatrix;

% hidden layer ���üh�v����s
newhiddenmatrix=hiddenmatrix;
for i=1:1:12
for j=1:1:4
newhiddenmatrix(j,i)=hiddenmatrix(j,i)+0.025*deltahidden(i)*input(iter,j);
end
end
hiddenmatrix=newhiddenmatrix;    
end


RMSE1(epoch) = sqrt(sum(t1)/75);
RMSE2(epoch) = sqrt(sum(t2)/30);

fprintf('epoch %.0f:  RMSE = %.3f\n',epoch, sqrt(sum(t1)/400));
end


fprintf('\nTotal number of epochs: %g\n', epoch);
fprintf('Final RMSE: %g\n', RMSE1(epoch));
%figure(1);
%plot(1:epoch,RMSE1(1:epoch),1:epoch,RMSE2(1:epoch));
legend('Training','Simulation');
ylabel('RMSE');xlabel('Epoch');



Train_Correct=0;

for i=1:75
    
    hiddensigma=input(i,:)*hiddenmatrix;
    hiddennet=logsig(hiddensigma);       
    outputsigma=hiddennet*outputmatrix;
    outputnet=purelin(outputsigma);
    out=[out;outputnet];
        if outputnet > target(i)-0.5 &  outputnet <= target(i)+0.5
            Train_Correct=Train_Correct+ 1;
        end
end


Simu_Correct=0;

for i=76:length(input)
    
    hiddensigma=input(i,:)*hiddenmatrix;
    hiddennet=logsig(hiddensigma);       
    outputsigma=hiddennet*outputmatrix;
    outputnet=purelin(outputsigma);
    outnet=[outnet;outputnet];
        if outputnet > target(i)-0.5 &  outputnet <= target(i)+0.5
            Simu_Correct=Simu_Correct+ 1;
        end
end
%figure(2);
%plot(76:length(input),target(76:length(input)),76:length(input),outnet(1:75))
legend('Function','Simulation');
Train_Percent= (Train_Correct) / 75;
Simu_Percent= (Simu_Correct) / (length(input)-75);
Train_correct_percent=Train_Percent
Simu_correct_percent=Simu_Percent



%figure(3)
%[m,b,r]=postreg(out',target(1:75)');