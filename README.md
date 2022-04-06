# SentenceCheckerNLP
Trained a neural network with a locally-stored dictionary and a set of correct sentences. Then tested its effectiveness using a set of both correct and incorrect sentences.

//Pseudocode of NLP Program

//Author: Kelly T.

Overall substructure of program:

At Start:

1. Connect to Dictionary API or load Dictionary 
2. Feed Neural Network with Syntactically correct sentences of various types and differing data sizes

At Runtime:

3. Allow Neural Network to process sentences 
3.1 Network uses self-learning algorithm to determine what constitutes a correct sentence.
4. Stop the self-learning after initial dataset has been processed.

5. Test the effectiveness of the NL processor by feeding it new sentences, some of which are correct and others incorrect
5.1 NL Processor uses the dictionary API to breakdown a sentence into its constituent parts, allowing it to apply its self-learned algorithm
	(For example, with a sentence "That dog is red", it will need to use a dictionary dataset or API to determine that dog is a noun)

6. Compare results for the NL Processor and measure the effectiveness



General Program Structure:

int main()

{

	ConnectToAPI();  //Or  LoadDictionaryFromLocalDrive();

	LoadLearningSet(); //Here it is fed the correct sentences from which to learn from

	SelfLearn(PreviousRules); //The previous rules are optional - from a previous use of selflearn

	//Network is ready now to accept input and output whether a sentence is correct or not
	
	while(more sentences are added)
	{
		Ask for sentence input
		
		CheckSentenceValidity(input);
		
		Output correctness
	}
	
}

ConnectToAPI()

{
	Connect to API and Test Connection
	DEBUG: check if calls are correct
}

LoadLearningSet()

{
	Open text file containing varying amount of sentences //100+
	Put into data structure (Array/List etc)
}

SelfLearn(PreviousRules)

{
	LoadPreviousRules if provided

	List possible attributes of sentences (e.g. Length, word type, neighbourhood analysis of words, word count, character examination)

	while (sentences are left to be examined)
	{
		Scan each provided sentence for attributes 

		Using attributes in a database/table format, determine which attributes best constitute a correct sentence and what their values should be //Multithreaded hopefully!

		Update self-learning criteria for correct sentences
	}	
}


CheckSentenceValidity(Input)

{
	Scan input sentence for attribute and give it a "score"
	Compare input sentence's "score" with the self-learning criteria to see if it passes
	
	Output whether it passes or not

	DEBUG: Output specifically the attributes and rules that the provided sentence failed to pass

}
