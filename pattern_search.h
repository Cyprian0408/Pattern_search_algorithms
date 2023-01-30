#include<iostream>
#include<string>
#include<vector>
#include <bits/stdc++.h>
using std::string;

bool is_input_valid(string pattern, string text) {
    return pattern.size() <= text.size();
}

//implementacja algorytmu N
void N_algorithm(string pattern, string text, std::vector<int> &results){
    if (!is_input_valid(pattern, text))
        return;
    int pattern_length=pattern.size();
    int text_length=text.size();
    bool check=false;
    string temp;
    //pętla przechodząca po całym tekście "bąblem" o wielkości równej długości wzorca porównująca wzorzec z wycinkiem tekstu o długości wzorca uzyskanym za pomocą funkcji substr
    for (int j=0; j<text_length-pattern_length+1;j++){
        temp=text.substr(j,pattern_length);
        if (temp==pattern){
            results.push_back(j);
            check=true;
        }
    }
    //sprawdzenie czy kiedykolwiek został znaleziony odpowiednik wzorca w tekście
}
//funkcja tworząca tabelę prefiksów umożliwiającą działanie algorytmu KMP
void generate_prefix_array(string pattern, int* prefix_array){
    int pattern_length=pattern.size();
    prefix_array[0]=0;
    int j=0;
    for (int i = 1; i < pattern_length; i++)
    {
        while (j>0&&pattern[j]!=pattern[i])  
        {
             j=prefix_array[j-1];
        }
        if(pattern[j]==pattern[i]){
            j++;
        }
        prefix_array[i]=j;
    }
}
//implementacja algorytmu KMP
void KMP_algorithm(string pattern, string text, std::vector<int> &results){
    if (!is_input_valid(pattern, text))
        return;
    int pattern_length=pattern.size();
    int text_length=text.size();
    int prefix_array[pattern_length];
    generate_prefix_array(pattern,prefix_array);
//for(int h=0;h<pattern_length;h++){
//    std::cout<<prefix_array[h]<<" ";
//}
//std::cout<<std::endl;
    int i = 0;
    int j = 0;
    while(i<text_length){
        //w momencie gdy jeden znak ze wzoru zgadza się ze znakiem z tekstu inkrementujemy wskaźniki
        if(pattern[j]==text[i]){
            i++;
            j++;
        }
        //w momencie gdy wskaźnik "przechodzący" przez poszukiwany wzorzec będzie równy długości wzorca to oznacza, że wzorzec został znaleziony w tekście 
        if(j==pattern_length){
            //std::cout<<i<<" ";
            results.push_back(i-j);
            j=prefix_array[j-1];
        }
        //w momencie, w którym znaki na odpowiednich wskaźnikach różnią się od siebie albo przesuwamy się jeden znak w tekście do przodu albo używamy tablicy prefiksów, aby przemieścić się w "zapisany w niej sposób"
        else if(i<text_length&&pattern[j]!=text[i]){
            if(j==0){
                i++;
            }
            else{
                j=prefix_array[j-1];
            }
        }

    }
    //std::cout<<std::endl;
}

// funkcje pomocnicze do KR
bool pattern_match(string pattern, string text, int first) {
    int last = first + pattern.length() - 1;
    for (int i = first; i <= last; ++i) {
        if (text[i] != pattern[i - first])
            return false;
    }
    return true;
}

long long hash(string text, int first, int last, long long alphabet_size, long long mod, long long &power) {
    long long result = 0;
    power = 1;
    for (int i = last; true; --i) {
        result = (result + (text[i] * power) % mod) % mod;
        if (i <= first)
            break;
        power = (power * alphabet_size) % mod;
    }
    return result;
}

// KR
void KR_algorithm(string pattern, string text, std::vector<int> &results){
    if (!is_input_valid(pattern, text))
        return;
    int pattern_length = pattern.size();
    int text_length = text.size();
    long long alphabet_size = 128; // rozmiar tablicy ascii
    long long mod = 99999997; // największa 8 cyfrowa liczba pierwsza
    long long power;
    long long pattern_hash = hash(pattern, 0, pattern_length - 1, alphabet_size, mod, power);
    long long text_hash = hash(text, 0, pattern_length - 1, alphabet_size, mod, power);
    int last_possible_index = text_length - pattern_length + 1;
    for (int i = 0; i <= last_possible_index; ++i) {
        // sprawdzamy tylko podciągi z tym samym hashem co wzorzec
        if (pattern_hash == text_hash && pattern_match(pattern, text, i)) {
            results.push_back(i);
        }
        // update hashu
        text_hash = (text_hash + mod - (text[i] * power) % mod) % mod;
        text_hash = (text_hash * alphabet_size) % mod;
        text_hash = (text_hash + text[i + pattern_length]) % mod;
    }
}

//implementacja funkcji pomocniczej umozliwiającej wypisanie zawartości kontenera
void print_result(std::vector<int> &results){
    for (std::vector<int>::const_iterator i = results.begin(); i != results.end(); ++i){
    std::cout << *i << ' ';
    }
    std::cout<<std::endl;
}
string generate_random_string(int size){
    string str;
    char c;
    for(int i=0; i<size; i++){
            c = rand() % 26 + 'A';
            str += c;
    }
return str;
}
string generate_random_two_letter_string(int size){
    string str;
    for(int i=0;i<size;i++){
        int a=rand()%2;
        if (a==0){
            str.push_back('a');
        }
        else{
            str.push_back('b');
        }
    }
return str;
}
void test_1(std::vector<int> &results_n,std::vector<int> &results_kmp, std::vector<int> &results_kr){
    string random_text=generate_random_string(100000);
    string random_pattern=generate_random_string(2);
    N_algorithm(random_pattern,random_text,results_n);
    KMP_algorithm(random_pattern,random_text,results_kmp);
    KR_algorithm(random_pattern,random_text,results_kr);
    std::cout<<std::endl;
    std::cout<<"Wyniki dla algorytmu N"<<std::endl;
    print_result(results_n);
    std::cout<<std::endl;
    std::cout<<"Wyniki dla algorytmu KMP"<<std::endl;
    print_result(results_kmp);
    std::cout<<std::endl;
    std::cout<<"Wyniki dla algorytmu KR"<<std::endl;
    print_result(results_kr);
}
void test_2(std::vector<int> &results_n,std::vector<int> &results_kmp, std::vector<int> &results_kr){
    std::cout<<"Test dla tekstu zbudowanego z dwóch liter alfabetu"<<std::endl;
    string random_text=generate_random_two_letter_string(30);
    string random_pattern=generate_random_two_letter_string(3);
    N_algorithm(random_pattern,random_text,results_n);
    KMP_algorithm(random_pattern,random_text,results_kmp);
    KR_algorithm(random_pattern,random_text,results_kr);
    std::cout<<std::endl;
    std::cout<<"Wyniki dla algorytmu N"<<std::endl;
    print_result(results_n);
    std::cout<<std::endl;
    std::cout<<"Wyniki dla algorytmu KMP"<<std::endl;
    print_result(results_kmp);
    std::cout<<std::endl;
    std::cout<<"Wyniki dla algorytmu KR"<<std::endl;
    print_result(results_kr);
}
void test_n_algorithm(){
    std::vector<int> results_n1, results_n2, results_n3, results_n4;
    string pattern="text";
    string case_1="";
    N_algorithm(pattern,case_1,results_n1);
    std::cout<<"Test algorytmu N"<<std::endl;
    std::cout<<"Test dla pustego stringa"<<std::endl;
    print_result(results_n1);
    string case_2="text";
    N_algorithm(pattern,case_2,results_n2);
    std::cout<<"Test dla napisu równego napisowi text"<<std::endl;
    print_result(results_n2);
    string case_3="texting";
    N_algorithm(pattern,case_3,results_n3);
    std::cout<<"Test dla napisu dłuższego od napisu text"<<std::endl;
    print_result(results_n3);
    string case_4="algorithm";
    N_algorithm(pattern,case_4,results_n4);
    std::cout<<"Napis nie występuje w text"<<std::endl;
    print_result(results_n4);
}
