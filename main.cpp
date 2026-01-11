#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

/*
    Quiz Application
    ----------------
    - Questions are read from a text file
    - Each question is asked only once per quiz
    - Scoring system: 3 wrong answers cancel 1 correct
    - Final score is calculated over 100 points
*/

int main()
{
	// Program initialization: locale and random seed
    // (Program baþlatma: dil ayarý ve rastgelelik tohumu)
    setlocale(LC_ALL, "Turkish");
    srand(time(NULL));
    
    // Variables for reading and storing question data
    // (Soru verilerini okumak ve tutmak için deðiþkenler)
	string line;
	string question, optionA, optionB, optionC, optionD, userAnswer, correctAnswer;
	char answer;
	int count, lineCount=0;
	
	// Variables for statistics and scoring
    // (Ýstatistik ve puan hesaplama deðiþkenleri)
	int trueNum=0, falseNum=0, emptyNum=0;
	float total=0.0, score=0.0;
	
	// Open questions file
    // (Sorular dosyasýný aç)
	ifstream file;
	file.open("questions.txt");
	
	// File open validation
    // (Dosya açma kontrolü)
	if(!file.is_open()){
		cout<<"DOSYA BULUNAMADI!";
		return 0;
	}
	
	// Count total number of questions in file
    // (Dosyadaki toplam soru sayýsýný hesapla)
	while(getline(file, line)){
		lineCount++; 
	}
	
	// Limit maximum number of questions to avoid overflow
    // (Dizi taþmasýný önlemek için maksimum soru sýnýrý)
	const int maxQuestions=200;
	if(lineCount>maxQuestions){
		cout<<"Dosyada çok fazla soru var! (MAX : "<<maxQuestions<<")";
		return 0;
	}
	
    // Tracks which questions have already been asked
    // (Daha önce sorulmuþ sorularý takip eder)
    bool used[maxQuestions]={false};
	
	int remainder=lineCount;
	int howMany;
	cout<<"- - - QUIZ - - -"<<endl;
	
	do{
		// Ask users how many questions they want
        // (Kullanýcýdan kaç soru istediðini al)
	cout<<"Kaç soruluk yarýþma istiyorsunuz? (1-"<<remainder<<"): ";
	cin>>howMany;
	
	    // Input validation
        // (Geçersiz giriþ kontrolü)
	if(howMany<1 || remainder<howMany){
		cout<<"Geçersiz sayý! Kalan soru sayýsý: "<<remainder;
	    continue; 
	}
	
	remainder-=howMany;
	correctAnswer = userAnswer ="";
	cout<<endl;
	cout<<"=== BÝLGÝ YARIÞMASI BAÞLADI ===\n"<<endl;
	
	for(int qn=0; qn<howMany; qn++){
	    file.close();
	    file.open("questions.txt");
	
	        // Select a random unused question index
            // (Daha önce sorulmamýþ rastgele soru seç)
	    int randomLine;
	    do{
	        randomLine=rand()%lineCount;
        }while(used[randomLine]==true);
    
            // Find the selected line in file
            // (Seçilen satýrý dosyada bul)
        int currentLine=0;
	    while(getline(file, line)){
		    if(currentLine==randomLine){
			    used[randomLine]=true;
			    break;
		    }currentLine++;
	    }
	    
	        // Parse the line separated by ';' into question, options, and answer
            // (Satýr ';' karakterine göre soru, þýklar ve doðru cevap olarak ayrýlýr)
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
			    else if(count==5)
			        correctAnswer+=char(line[j]);
			}
		cout<<"Soru "<<qn+1<<": "<<question<<endl;
		cout<<"A) "<<optionA<<endl;
		cout<<"B) "<<optionB<<endl;
		cout<<"C) "<<optionC<<endl;
		cout<<"D) "<<optionD<<endl;
		cout<<"Cevabýnýz (A-D, boþ için X): ";
		cin>>answer;
		cout<<endl;
		
		    // Normalize and validate user answer
            // (Cevabý büyük harfe çevir ve doðrula)
		answer=char(toupper(answer));
		    if(answer!='A' && answer!='B' && answer!='C' && answer!='D' && answer!='X'){
			    cout<<"Geçersiz cevap, boþ sayýldý.\n"<<endl;
		    	answer='X';
		    } 
		userAnswer+=answer;
	    }
	    
	        // Results and scoring
            // (Sonuçlar ve puan hesaplama)
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
		
		    // Net calculation: 3 wrong answers remove 1 correct
            // (Net hesaplama: 3 yanlýþ 1 doðruyu götürür)
		total=trueNum-(falseNum/3.0);
		
		cout<<"\n--- ÝSTATÝSTÝKLER ---"<<endl;
		cout<<"Doðru : "<<trueNum<<endl;
		cout<<"Yanlýþ: "<<falseNum<<endl;
		cout<<"Boþ   : "<<emptyNum<<endl;
		cout<<"Net   : "<<total<<endl;
		
		    // Convert net score to a 100-point scale
            // (Net puan 100'lük sisteme çevrilir)
		if(total<0) total=0;
		score=total*(100.0/howMany);
		cout<<"\nPuanýnýz: "<<score<<" / 100"<<endl;
		
	    char again;
	    cout<<"\nTekrar oynamak ister misiniz? (E/H): ";
	    cin>>again;
	    
	    if(again=='E' || again=='e')
	    cout<<endl;
	    else if(again=='H' || again=='h')
	    break;
	    else
	    cout<<"Geçerli cevap girilmediði için devam ediliyor..."<<endl;
	    } while(1);
	    
	file.close();
	return 0;
}
