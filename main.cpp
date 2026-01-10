#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Turkish");
    srand(time(NULL));
	string line;
	string question, optionA, optionB, optionC, optionD, userAnswer, correctAnswer;
	char answer;
	int count;
	int trueNum=0, falseNum=0, emptyNum=0;
	float total=0.0, score=0.0;
	
	ifstream file;
	file.open("questions.txt");
	
	if(!file.is_open()){
		cout<<"DOSYA BULUNAMADI!";
		return 0;
	}
	
	cout<<"- - - QUIZ - - -"<<endl;
	
	int lineCount=0;
	while(getline(file, line)){
		lineCount++;
	}
	bool used[lineCount]={false};
	int remainder=lineCount;
	int howMany;
	
	for(int q=1; q<=howMany; q++){
	int questionNumber=0;
	cout<<"Kaç soruluk yarýþma istiyorsunuz? (1-"<<remainder<<"): ";
	cin>>howMany;
	remainder-=howMany;
	cout<<endl;
	cout<<"=== BÝLGÝ YARIÞMASI BAÞLADI ===\n"<<endl;
	
	file.close();
	file.open("questions.txt");
	
	int randomLine;
	do{
	    randomLine=(rand()%lineCount+1);
    }while(used[randomLine]==true);
    
    int currentLine=1;
	while(getline(file, line)){
		if(currentLine==randomLine){
			used[randomLine]=true;
			break;
		}currentLine++;
	}
	
	correctAnswer = userAnswer ="";
	
	while(getline(file, line)){
		question = optionA = optionB = optionC = optionD ="";
		count=0;
			for(int j=0; j<line.length(); j++){
				if(line[j]==';'){
				    count++;
				    continue;
			    }
			    if(count==0)
			        question+=line[j];
			    else if(count==1)
			        optionA+=line[j];
			    else if(count==2)
			        optionB+=line[j];
			    else if(count==3)
			        optionC+=line[j];
			    else if(count==4)
			        optionD+=line[j];
			    else
			        correctAnswer+=line[j];
			}
			questionNumber++;
		cout<<"Soru "<<questionNumber<<": "<<question<<endl;
		cout<<"A) "<<optionA<<endl;
		cout<<"B) "<<optionB<<endl;
		cout<<"C) "<<optionC<<endl;
		cout<<"D) "<<optionD<<endl;
		cout<<"Cevabiniz (A-D, boþ için X): ";
		cin>>answer;
		cout<<endl;
		
		userAnswer+=char(toupper(answer));
		if(questionNumber==howMany) break;
	    }
	    
	    cout<<"=== SONUÇ RAPORU ===\n"<<endl;
	    count=1, trueNum=0, emptyNum=0, falseNum=0, total=0.0, score=0.0;
	    for(int i=0; i<howMany; i++){
	    	cout<<"Soru "<<count++<<" | Senin cevabin: "<<userAnswer[i]<<" | Doðru cevap: "<<correctAnswer[i]<<endl;
	    	
	    	if((toupper(userAnswer[i]))==correctAnswer[i])
	    	trueNum++;
	    	else if(userAnswer[i]=='X')
	    	emptyNum++;
	    	else
	    	falseNum++;
		}
		total=trueNum-falseNum/3.0;
		score=fabs(total)*(100.0/howMany);
		
		cout<<"\n--- ÝSTATÝSTÝKLER ---"<<endl;
		cout<<"Doðru : "<<trueNum<<endl;
		cout<<"Yanlýþ: "<<falseNum<<endl;
		cout<<"Boþ   : "<<emptyNum<<endl;
		cout<<"Net   : "<<total<<endl;
		
		cout<<"\nPuanýnýz: "<<score<<" / 100"<<endl;
		
	    char again;
	    cout<<"\nTekrar oynamak ister misiniz? (E/H): ";
	    cin>>again;
	    
	    if(again=='E' || again=='e')
	    cout<<endl;
	    else if(again=='H' || again=='h')
	    break;
	    }
	    
	file.close();
	return 0;
}
