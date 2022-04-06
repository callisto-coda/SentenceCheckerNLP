// SentenceChecker.cpp : Defines the entry point for the console application.
// Author : Kelly Trueman

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

bool noun_found = false;
bool verb_found = false;
bool adjective_found = false;

float n_w = 0;
float v_w = 0;
float a_w = 0;

float nv_w = 0;
float na_w = 0;
float av_w = 0;

float avn_w = 0;



bool dictionaryCheck(string word) {
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	bool found = false;
	ifstream nouns;
	ifstream verbs;
	ifstream adjectives;
	int pos;
	string line;

	

	nouns.open("nouns.txt");
	verbs.open("verbs.txt");
	adjectives.open("adjectives.txt");

	if (!nouns)
		cout << "Unable to open nouns.txt\n";
	if (!verbs)
		cout << "Unable to open verbs.txt\n";
	if (!adjectives)
		cout << "Unable to open adjectives.txt\n";


	while (nouns.good())
	{
		
		getline(nouns, line); // get line from file
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		pos = line.compare(word); // search
		if (pos == 0) // compare returns 0 if they match
		{
			cout << ": found in noun dictionary\n";
			noun_found = true;
			found = true;
		}
	}
	

	while (verbs.good())
	{
		getline(verbs, line);
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		pos = line.compare(word);
		if (pos == 0)
		{
			cout << ": found in verb dictionary\n";
			verb_found = true;
			found = true;
		}
	}

	while (adjectives.good())
	{
		getline(adjectives, line);
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		pos = line.compare(word);
		if (pos == 0)
		{
			cout << ": found in adjectives dictionary\n";
			adjective_found = true;
			found = true;
		}
	}
	return found;
}


void displayCurrentWeights(float n, float v, float a, float nv, float na, float va, float avn)
{
	cout << "Noun Weight: " << n << "  --  Verb Weight: " << v << "  --   Adj. Weight: " << a << "  --   Noun+Verb Weight: " << nv << "  --   Noun+Adj Weight: " << na << "   --   Verb+Adj Weight: " << va << "  --   Noun+Verb+Adj Weight: " << avn << endl;


}

void readSentence() {

	ifstream sentences;

	string delimiter = " ";
	string token;
	string s;
	string line;
	string strArray[100];

	size_t pos = 0;

	int index = 0;
	int sentencenum = 0;
	int readpoint = 0;


	//Initiating all weights randomly
	n_w = (double)rand() / RAND_MAX;
	a_w = (double)rand() / RAND_MAX;
	v_w = (double)rand() / RAND_MAX;
	na_w = (double)rand() / RAND_MAX;
	nv_w = (double)rand() / RAND_MAX;
	av_w = (double)rand() / RAND_MAX;
	avn_w = (double)rand() / RAND_MAX;

	displayCurrentWeights(n_w, v_w, a_w, nv_w, na_w, av_w, avn_w);

	sentences.open("sentences.txt");
	if (!sentences)
		cout << "Unable to open sentences.txt\n";

	while (getline(sentences, line)) {



		sentencenum++;
		s = s + line;
		readpoint = index;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			strArray[index] = token; // put single word into an array element
			index++;
			s.erase(0, pos + delimiter.length());
		}
		strArray[index] = s; //final word
		s.erase();

		cout << "Sentence " << sentencenum << ":\n";

		noun_found = false;
		adjective_found = false;
		verb_found = false;

		for (int i = readpoint; i <= index; i++) {
			cout << "word: " << strArray[i]; //output each word
			if (!dictionaryCheck(strArray[i]))
				cout << ": not found\n";
		}


		//All sentences must have a verb and a noun - TRAINING N_N HERE
		if (noun_found == true)
			n_w = ((1 - n_w) / 2) + n_w;
		else
			n_w = n_w / 2;

		if (verb_found == true)
			v_w = ((1 - v_w) / 2) + v_w;
		else
			v_w = v_w / 2;

		if (adjective_found == true)
			a_w = ((1 - a_w) / 2) + a_w;
		else
			a_w = a_w / 2;

		if (noun_found && verb_found)
			nv_w = ((1 - nv_w) / 2) + nv_w;
		else
			nv_w = nv_w / 2;

		if (noun_found && adjective_found)
			na_w = ((1 - na_w) / 2) + na_w;
		else
			na_w = na_w / 2;

		if (verb_found && adjective_found)
			av_w = ((1 - av_w) / 2) + av_w;
		else
			av_w = av_w / 2;

		if (noun_found && verb_found && adjective_found)
			avn_w = ((1 - avn_w) / 2) + avn_w;
		else
			avn_w = avn_w / 2;


		displayCurrentWeights(n_w, v_w, a_w, nv_w, na_w, av_w, avn_w);

		noun_found = false;
		adjective_found = false;
		verb_found = false;

	}

	cout << "\nTraining completed with " << sentencenum << " cycles. The neural weights are below: " << endl;
	displayCurrentWeights(n_w, v_w, a_w, nv_w, na_w, av_w, avn_w);

	return;
}

void testSentence()
{
	ifstream sentences_test;

	string delimiter = " ";
	string token;
	string s;
	string line;
	string strArray[100];

	size_t pos = 0;

	bool isSentence = false;

	int index = 0;
	int sentencenum = 0;
	int readpoint = 0;

	

	sentences_test.open("test.txt");
	if (!sentences_test)
		cout << "Unable to open test.txt\n";

	while (getline(sentences_test, line)) {

		isSentence = false;

		sentencenum++;
		s = s + line;
		readpoint = index;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			strArray[index] = token; // put single word into an array element
			index++;
			s.erase(0, pos + delimiter.length());
		}
		strArray[index] = s; //final word
		s.erase();

		cout << "Sentence " << sentencenum << ":\n";

		noun_found = false;
		adjective_found = false;
		verb_found = false;

		for (int i = readpoint; i <= index; i++) {
			cout << "word: " << strArray[i]; //output each word
			if (!dictionaryCheck(strArray[i]))
				cout << ": not found\n";
		}





		

		double sentenceScore = (noun_found * n_w + verb_found * v_w + (noun_found * verb_found) * nv_w) / 3;

		if (sentenceScore > 0.90)
		{
			isSentence = true;
			cout << " --- " << line << " --- is a sentence with a score of " << sentenceScore << endl;
		}
		else
		{
			isSentence = false;
			cout << " --- " << line << " --- is NOT a sentence with a score of " << sentenceScore << endl;
		}



		noun_found = false;
		adjective_found = false;
		verb_found = false;

	}
	return;
}


int main(int argc, char * argv[])
{
	srand(time(NULL));


	cout << "\n\nInitiating Training of NN with sentences from Sentences.txt - neural weights will be adjusted with each sentence " << endl;

	readSentence();


	cout << "\n\nInitiating testing of NN with test sentences from test.txt" << endl;

	testSentence();
	return 0;
}

