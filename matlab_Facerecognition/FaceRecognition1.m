function[outputnet,target]=FaceRecognition1
people=40;
withinsample=5;
principleenum=50;
FFACE=[];
for k=1:1:people
for m=1:2:10
    matchstring=['ORL3232' '\' num2str(k) '\' num2str(m) '.bmp'];
    matchX=imread(matchstring);
    matchX=double(matchX);
    if(k==1&&m==1)
        [row,col]=size(matchX);
    end
    matchtempF=[];
    %arrange the image into a vector
    for n=1:row
        matchtempF=[matchtempF,matchX(n,:)];
    end
    FFACE=[FFACE;matchtempF];
end
end
[FFACERow,col]=size(FFACE);


TotalMeanFACE=mean(FFACE)
for i=1:1:FFACERow 
    FFACE(i,:)=FFACE(i,:)-TotalMeanFACE; 
end

SST=FFACE'*FFACE;
[pca,latent] = eig(SST);

eigvalue=diag(latent);   % extract the diagnal only

[junk, index] = sort(eigvalue, 'descend');

pca1 = pca(:, index);

eigvalue=eigvalue(index);

projectPCA=pca1(:,1:20);     % extract the principle component


pcaTotal=[];     

for i=1:1:FFACERow
    temp=FFACE(i,:);
    temp=temp*projectPCA;        % 內積求新座標值
    pcaTotal=[pcaTotal;temp];    %儲存所有投影至PCA空間中的訓練影像
end

%---------------------------------


%++++++++ LDA transform ++++++++++++++++++++++++++++++++    
for i=1:5:5*20
    within=pcaTotal(i:i+5-1,:);   %暫存單一類別PCA空間中訓練影像 
    if (i==1)       
        SW=within'*within;          %SW=cov(within);
        ClassMean=mean(within);
    end
    if (i>1)
       SW=SW+within'*within;        %SW=SW+cov(within);
       ClassMean=[ClassMean;mean(within)]; % this matrix is for Between
    end
end % end of i
%--------------------------------------------------


SB=ClassMean' * ClassMean;  % SB=cov(ClassMean);

[eigvector, eigvalue] = eig(inv(SW)*SB);  %--->   arg max (SB/SW)
eigvalue = diag(eigvalue);
[junk, index] = sort(eigvalue, 'descend');
eigvalue = eigvalue(index);
projectLDA = eigvector(:,index);

prototype=pcaTotal*projectLDA(:,1:5); %

load IRIS_OUT.csv;
input = prototype;
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

hiddenmatrix=zeros(5,12);
for i=1:1:5
 for j=1:1:12
   hiddenmatrix(i,j)=rand;
 end
end



%start

RMSE1=zeros(100,1);
RMSE2=zeros(100,1);


% Training
for epoch=1:1:100
t1=[];
t2=[];
for iter=1:1:75

% forward 前傳部分

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





% backward part 倒傳部分
% delta of outputmatrix 輸出層的 delta
doutputnet=dpurelin(outputsigma);
deltaoutput=(target(iter)-outputnet)*doutputnet;
error=target(iter)-outputnet;
t1=[t1;error.^2];


% delta of hidden layer 隱藏層的 delta
tempdelta=deltaoutput*outputmatrix;
transfer=dlogsig(hiddensigma,logsig(hiddensigma));
deltahidden=[];
for i=1:1:12
deltahidden=[deltahidden;tempdelta(i)*transfer(i)];
end

% output layer weight update 輸出層權重更新
newoutputmatrix=outputmatrix+0.025*(deltaoutput*hiddennet)';
outputmatrix=newoutputmatrix;

% hidden layer 隱藏層權重更新
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


%round2
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

for i=76:length(target)
    
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