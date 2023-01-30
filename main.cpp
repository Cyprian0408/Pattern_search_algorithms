#include<fstream>
#include <iostream>
#include<bits/stdc++.h>
#include "pattern_search.h"
#include"pbPlots.hpp"
#include"supportLib.hpp"

int main(){
    std::fstream file;
    int size_of_text=100000;
    int j=0;
    std::vector<int> results_n, results_kmp, results_kr;
    double n[]={100,200,300,400,500,600,700,800,900,1000};
    int size=sizeof(n)/sizeof(double);
    double time_taken_by_n_algorithm[size];
    double time_taken_by_kmp_algorithm[size];
    double time_taken_by_kr_algorithm[size];
    std::chrono::time_point<std::chrono::high_resolution_clock> start,end;
    string s,text;
    file.open("pan.txt");
    if (file.fail()){
        std::cout<<"Error"<<std::endl;
        return 1;       
    }
    while(getline(file, s)){
        text=text+"\n"+s;
    }
    file.close();
    string pattern="cokolwiek";
    //badanie czasu algorytmu n
    for (int i=0;i<size;i++){
        string substr=text.substr(0,n[i]);
        std::ios_base::sync_with_stdio(false);
        //rozpoczęcie badania czasu trwania algorytmu
        start = std::chrono::high_resolution_clock::now();
        N_algorithm(pattern,substr,results_n);
        end = std::chrono::high_resolution_clock::now();
        time_taken_by_n_algorithm[i]={double(((std::chrono::duration<double>)(end-start)).count())};
        results_n.clear();
    }
    //badanie czasu algorytmu kmp
    for (int i=0;i<size;i++){
        string substr=text.substr(0,n[i]);
        std::ios_base::sync_with_stdio(false);
        //rozpoczęcie badania czasu trwania algorytmu
        start = std::chrono::high_resolution_clock::now();
        KMP_algorithm(pattern,substr,results_kmp);
        end = std::chrono::high_resolution_clock::now();
        time_taken_by_kmp_algorithm[i]={double(((std::chrono::duration<double>)(end-start)).count())};
        results_kmp.clear();
    }
    //badanie czasu algorytmu kr
    for (int i=0;i<size;i++){
        string substr=text.substr(0,n[i]);
        std::ios_base::sync_with_stdio(false);
        //rozpoczęcie badania czasu trwania algorytmu
        start = std::chrono::high_resolution_clock::now();
        KR_algorithm(pattern,substr,results_kmp);
        end = std::chrono::high_resolution_clock::now();
        time_taken_by_kr_algorithm[i]={double(((std::chrono::duration<double>)(end-start)).count())};
        results_kr.clear();
    }
    //testowanie poprawności algorytmów 
    test_n_algorithm();
    test_1(results_n,results_kmp,results_kr);
    results_n.clear();
    results_kmp.clear();
    results_kr.clear();
    test_2(results_n,results_kmp,results_kr);
    results_n.clear();
    results_kmp.clear();
    results_kr.clear();
    //przygotowanie danych do sporządzenia wykresów
    std::vector<double> time_n, time_kmp, time_kr, time_m, num;
    for(int i=0;i<size;i++){
        time_n.push_back(time_taken_by_n_algorithm[i]);
    }
    for(int i=0;i<size;i++){
        time_kmp.push_back(time_taken_by_kmp_algorithm[i]);
    }
    for(int i=0;i<size;i++){
        time_kr.push_back(time_taken_by_kr_algorithm[i]);
    }
    for(int i=0;i<size;i++){
        num.push_back(n[i]);
    }
    ////tworzenie wykresów
    //bool success;
    //StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    //RGBABitmapImageReference *imageRef=CreateRGBABitmapImageReference();
    //success=DrawScatterPlot(imageRef, 600, 400, &num, &time_n,errorMessage);
    //if(success){
	//	std::vector<double> *pngdata = ConvertToPNG(imageRef->image);
	//	WriteToFile(pngdata, "N_algorithm_time.png");
	//	DeleteImage(imageRef->image);
	//}else{
	//	std::cerr << "Error: ";
	//	for(wchar_t c : *errorMessage->string){
	//		std::wcerr << c;
	//	}
	//	std::cerr << std::endl;
	//}
    //success=DrawScatterPlot(imageRef, 600, 400, &num, &time_kmp,errorMessage);
    //if(success){
	//	std::vector<double> *pngdata = ConvertToPNG(imageRef->image);
	//	WriteToFile(pngdata, "KMP_algorithm_time.png");
	//	DeleteImage(imageRef->image);
	//}else{
	//	std::cerr << "Error: ";
	//	for(wchar_t c : *errorMessage->string){
	//		std::wcerr << c;
	//	}
	//	std::cerr << std::endl;
	//}
	//success=DrawScatterPlot(imageRef, 600, 400, &num, &time_kr,errorMessage);
    //if(success){
	//	std::vector<double> *pngdata = ConvertToPNG(imageRef->image);
	//	WriteToFile(pngdata, "KR_algorithm_time.png");
	//	DeleteImage(imageRef->image);
	//}else{
	//	std::cerr << "Error: ";
	//	for(wchar_t c : *errorMessage->string){
	//		std::wcerr << c;
	//	}
	//	std::cerr << std::endl;
	//}
    //return 0;
}//