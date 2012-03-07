/*
 * Evolver.cpp
 *
 *  Created on: 3-feb.-2012
 *      Author: Skidzobolder
 */

#include "Evolver.h"




void Evolver::readConfig(std::string strFileName)
{
	std::ifstream t(strFileName.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();

	Evolver::traverse_xml(buffer.str());

	Evolver::printSettings();
}

void Evolver::traverse_xml(const std::string& input_xml)
{

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Config");
    m_strTitle = rootNode->first_node("Title")->value();
    m_strDescription = rootNode->first_node("Description")->value();
    m_strPath = rootNode->first_node("DirectoryPath")->value();
    m_eGenomeType = static_cast<GenomeType> (atoi(rootNode->first_node("GenomeType")->value()));

    rapidxml::xml_node<>* settingsNode = rootNode->first_node("Settings");
    m_nPopulationSize = atoi(settingsNode->first_node("PopulationSize")->value());
    m_dTruncation = atof(settingsNode->first_node("Truncation")->value());
    m_eNormalization = static_cast<NormalizationType> (atoi(settingsNode->first_node("Truncation")->first_attribute("normalization")->value()));
    m_bElitism = (settingsNode->first_node("Elitism")->value() == std::string("true"))? true: false;
    m_nMaxParents = atoi(settingsNode->first_node("MaxParents")->value());
    m_dTargetFitness =atof(settingsNode->first_node("TargetFitness")->value());
    m_eRecombination = static_cast<RecombinationType> (atoi(settingsNode->first_node("Recombination")->value()));
    //check if there is a "tournament" attribute, if not, set tournament size to 1.
    m_nTournamentSize = settingsNode->first_node("Recombination")->first_attribute("tournament")?atoi(settingsNode->first_node("Recombination")->first_attribute("tournament")->value()):1;

    rapidxml::xml_node<>* terminationNode = settingsNode->first_node("Termination");
    m_nMaxGenerations = terminationNode->first_node("MaxGenerations")? atoi(terminationNode->first_node("MaxGenerations")->value()) : 0;
    m_nMaxTimeTotal = terminationNode->first_node("MaxTimeTotal")? atoi(terminationNode->first_node("MaxTimeTotal")->value()) : 0;
    m_nMaxTimeGeneration = terminationNode->first_node("MaxTimeGeneration")? atoi(terminationNode->first_node("MaxTimeGeneration")->value()) : 0;
    m_nStagnation = terminationNode->first_node("Stagnation")? atoi(terminationNode->first_node("Stagnation")->value()) : 0;


    rapidxml::xml_node<>* mutationsNode = rootNode->first_node("Mutations");
    if(mutationsNode->first_node("Binary"))
    	sMutationChances.BinaryMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("Binary"));

    if(mutationsNode->first_node("Integer"))
    	sMutationChances.IntegerMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("Integer"));

    if(mutationsNode->first_node("Double"))
    	sMutationChances.DoubleMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("Double"));

    if(mutationsNode->first_node("Alphanum"))
    	sMutationChances.AlphanumMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("Alphanum"));

    if(mutationsNode->first_node("Custom"))
    	sMutationChances.CustomMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("Custom"));

    if(mutationsNode->first_node("Tree"))
    	sMutationChances.TreeMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("Tree"));

    if(mutationsNode->first_node("List"))
    	sMutationChances.ListMutationChance = Evolver::SetMutationChance(mutationsNode->first_node("List"));

}

void Evolver::printSettings(){
	std::cout << "Config file loaded:" << std::endl;
	std::cout << "Title: " << m_strTitle << std::endl;
	std::cout << "Description: " << m_strDescription << std::endl;
	std::cout << "Directory path: " << m_strPath << std::endl;
	std::cout << "PopulationSize: " << m_nPopulationSize << std::endl;
	std::cout << "Max Generations: " << m_nMaxGenerations << std::endl << std::endl;

	std::cout << "Mutation chances:" << std::endl;
	std::cout << "Binary:" << std::endl;
	Evolver::printMutationChance(sMutationChances.BinaryMutationChance);
	std::cout << "Integer:" << std::endl;
	Evolver::printMutationChance(sMutationChances.IntegerMutationChance);
	std::cout << "Double:" << std::endl;
	Evolver::printMutationChance(sMutationChances.DoubleMutationChance);
	std::cout << "Alphanum:" << std::endl;
	Evolver::printMutationChance(sMutationChances.AlphanumMutationChance);
	std::cout << "Custom:" << std::endl;
	Evolver::printMutationChance(sMutationChances.CustomMutationChance);
	std::cout << "Tree:" << std::endl;
	Evolver::printMutationChance(sMutationChances.TreeMutationChance);
	std::cout << "List:" << std::endl;
	Evolver::printMutationChance(sMutationChances.ListMutationChance);
}

void Evolver::printMutationChance(MutationChance mutationChance){
	std::cout << " BitString: " << mutationChance.dBitString << std::endl
			<< " FlipBits: " << mutationChance.dFlipBits << std::endl
			<< " Boundary: " << mutationChance.dBoundary << std::endl
			<< " Uniform: " << mutationChance.dUniform << std::endl
			<< " Gaussian: " << mutationChance.dGaussian  << " sigma: " << mutationChance.dGaussianSigma << std::endl
			<< " Duplication: " << mutationChance.dDuplication << std::endl
			<< " Deletion: " << mutationChance.dDeletion << std::endl
			<< " Insertion: " << mutationChance.dInsertion << std::endl
			<< " Swap: " << mutationChance.dSwap << std::endl
			<< " Gene Duplication: " << mutationChance.dGeneDuplication << std::endl
			<< " Gene Deletion: " << mutationChance.dGeneDeletion << std::endl
			<< " Gene Insertion: " << mutationChance.dGeneInsertion << std::endl
			<< " Gene Swap: " << mutationChance.dGeneSwap << std::endl << std::endl;
}

void Evolver::start(){

	//create pointer to array of Rosetta objects for population and next generation
	Rosetta* pacPopulation = new Rosetta[m_nPopulationSize];
	Rosetta* pacNextGeneration = new Rosetta[m_nPopulationSize];



	//initialize Rosetta objects
	for(int i = 0; i<m_nPopulationSize; i++ ){
		pacPopulation[i].SetGenomeType(m_eGenomeType);
		pacPopulation[i].initGenome();
		//put random data in all genomes
		pacPopulation[i].randomGenome();
	}

	std::cout << pacPopulation[0].cGenome.GetXML() << std::endl;
	//create Aperture object

	m_nGeneration = 1;
	m_dHighestFitness = 0;
	m_vdFitness.clear();
	m_vdGenerationTime.clear();



	clock_t start, finish;
//do until maxGenerations or a suitable solution is reached
while(DoNextGeneration()){
	start = clock();
	std::cout << "Generation " << m_nGeneration;

	//calculate fitness
	for(int i = 0; i<m_nPopulationSize; i++ ){
		pacPopulation[i].CalcFitness();
		//std::cout << "fitness of " << i << ": " << pacPopulation[i].GetFitness() << std::endl;
	}

	std::vector<Parent> vsSelection = MakeSelection(pacPopulation);
	std::cout << "\tHighest fitness: " << vsSelection[0].dFitness ;
	m_dHighestFitness = vsSelection[0].dFitness;
	m_vdFitness.push_back(vsSelection[0].dFitness);

/*	for(unsigned int i = 0; i < vsSelection.size(); i++ ){
		std::cout << "Parent " << i << " index: " << vsSelection[i].nIndex;
		std::cout << " fitness: " << vsSelection[i].dFitness;
		std::cout << " normalized fitness: " << vsSelection[i].dNormalizedFitness;
		std::cout << " accumulated fitness: " << vsSelection[i].dAccumulatedNormalizedFitness << std::endl;
	}
*/


	//if elitims is true, set the first genome of the next generation to the genome with highest fitness
	if(m_bElitism){
		pacNextGeneration[0].SetGenome(pacPopulation[vsSelection[0].nIndex].cGenome.GetXML());
		pacNextGeneration[0].SetGenomeType(m_eGenomeType);
	}

	//do recombinations
	for(int i = m_bElitism; i<m_nPopulationSize; i++ ){		//if elitism is true, the for loop begins at 1 instead of 0
		m_cRecombination.Clear();		//make sure new recombination is empty

		switch (m_eRecombination)
		{
			case RECOMBINATION_RWS:
				RWS(vsSelection, pacPopulation);
				break;
			case RECOMBINATION_SUS:
				SUS(vsSelection, pacPopulation);
				break;
			case RECOMBINATION_TOURNAMENT:
				Tournament(vsSelection, pacPopulation);
				break;

			default:
				std::cout << "Unknown recombination type" << std::endl;
				break;
		}

		pacNextGeneration[i].SetGenome(m_cRecombination.RecombinedGenomeXML());
		pacNextGeneration[i].SetGenomeType(m_eGenomeType);
	}

	//do mutations
	//std::cout << pacNextGeneration[0].cGenome.GetXML() << std::endl;
	for(int i = 0; i<m_nPopulationSize; i++ ){
		pacNextGeneration[i].DoMutations(sMutationChances);

	}




	//copy next generation to population
	for(int i = 0; i<m_nPopulationSize; i++ ){
		pacPopulation[i].SetGenome(pacNextGeneration[i].cGenome.GetXML());
		pacPopulation[i].SetGenomeType(m_eGenomeType);
	}

	m_nGeneration++;
	finish = clock();
	m_vdGenerationTime.push_back((double) (finish - start)/CLOCKS_PER_SEC);
	std::cout << "\ttime: " << (double) (finish - start)/CLOCKS_PER_SEC  << std::endl;
}
//loop

	std::cout << pacNextGeneration[0].cGenome.GetXML() << std::endl;




	delete[] pacPopulation;	//clean up memory
	delete[] pacNextGeneration;

	std::cout << "Evolution finished" << std::endl;
}

bool Evolver::DoNextGeneration(){
	bool doNextGeneration = true;

	//see if the evolution has stagnated
	if(m_nStagnation && m_nGeneration > m_nStagnation){
		bool stagnation = true;
		for(int i = 0; i < m_nStagnation; i++){
			if( m_vdFitness.at(m_vdFitness.size()-1-i) != m_dHighestFitness) {
				stagnation = false;
				break;
			}
		}
		stagnation == true ? doNextGeneration = false : doNextGeneration = true;
		if (stagnation){
			std::cout << "Evolution has stagnated." << std::endl;
		}
	}


	//see if maximum number of generations is reached
	if(m_nMaxGenerations && m_nGeneration > m_nMaxGenerations){
		doNextGeneration = false;
		std::cout << "Maximum number of generations reached" << std::endl;
	}

	//see if a suitable solution is found
	if(m_dTargetFitness && m_dHighestFitness >= m_dTargetFitness){
		doNextGeneration = false;
		std::cout << "Found suitable solution " << m_dHighestFitness  << std::endl;
	}

	//see if the time for the last generation was more than the maximum time allowed
	if(m_nMaxTimeGeneration && m_nGeneration > 1 && m_vdGenerationTime.at(m_vdGenerationTime.size()-1) >= m_nMaxTimeGeneration ){
		doNextGeneration = false;
		std::cout << "Maximum time to calculate each generation has been reached." << std::endl;

	}

	//see if the total time is more than the maximum time allowed
	double dTotalTime = 0;
	for(unsigned int i = 0; i < m_vdGenerationTime.size(); i++){
		dTotalTime += m_vdGenerationTime.at(i);
	}
	if(m_nMaxTimeTotal && dTotalTime >= m_nMaxTimeTotal ){
		doNextGeneration = false;
		std::cout << "Maximum total time has been reached." << std::endl;
	}


	if(doNextGeneration == false){
		std::cout << "Stopping Evolution" << std::endl;
	}


	return doNextGeneration;
}

std::vector<Parent> Evolver::MakeSelection(Rosetta* population){
	//calculate which genomes are selected as possible parents
	int nSelectedGenomes;  		//number of genomes that get to have offspring

	assert(m_dTruncation > 0 && m_dTruncation <= 100);	//Truncation must be greater than 0 and smaller or equal to 100.
	nSelectedGenomes = m_nPopulationSize * m_dTruncation/100;

	std::vector<Parent> vsParent(nSelectedGenomes);

	int nParentsAdded = 0;

	double dFitnessBelow = -1.0;
	while(nParentsAdded < nSelectedGenomes){
		double dHighestFitness = 0.0;
		int nFitnessOccurences = 0;

		for(int i = 0; i<m_nPopulationSize; i++ ){

			if(population[i].GetFitness() == dHighestFitness && nParentsAdded+nFitnessOccurences < nSelectedGenomes){
				nFitnessOccurences++;

				vsParent[nParentsAdded+nFitnessOccurences-1].nIndex = i;
				vsParent[nParentsAdded+nFitnessOccurences-1].dFitness = population[i].GetFitness();
			}

			if(population[i].GetFitness() > dHighestFitness && (population[i].GetFitness() < dFitnessBelow || dFitnessBelow == -1.0)){
				dHighestFitness = population[i].GetFitness();
				nFitnessOccurences = 1;

				vsParent[nParentsAdded].nIndex = i;
				vsParent[nParentsAdded].dFitness = population[i].GetFitness();
			}
		}
		dFitnessBelow = dHighestFitness;
		nParentsAdded = nParentsAdded + nFitnessOccurences;

	}



	//calculate chance to make offspring for each parent
	double dTotalFitness = 0;
	for(int i = 0; i<nSelectedGenomes; i++ ){
		dTotalFitness += vsParent[i].dFitness;
	}

	//some initializations to be used in the normalization
	assert(dTotalFitness != 0);		//check to avoid divide by zero error
	double dTmpAccumulatedFitness = 0.0;
	int nTotalUnits = 0;

	if(m_eNormalization == NORM_RANK){			//totalUnits is only needed for rank based selection , totalUnits = permutation of nSelectedGenomes
		for(int j = 1; j<=nSelectedGenomes; j++ ){
    		nTotalUnits += j;
		}
	}

	//normalize the fitness for each genome based on normalization method
	for(int i = 0; i<nSelectedGenomes; i++ ){
		switch (m_eNormalization)
	    {
    		case NORM_PROPORTIONAL: //chance is proportional based on fitness
    			vsParent[i].dNormalizedFitness = vsParent[i].dFitness/dTotalFitness;
    			vsParent[i].dAccumulatedNormalizedFitness = dTmpAccumulatedFitness;
    			break;
    		case NORM_RANK:		//for example: if you have a selection of 10 genomes, the first genome is 10 times more likely to be picked than the last, the second is 9 times, third is 8 times, ...
    			vsParent[i].dNormalizedFitness = ((nSelectedGenomes-i)/(double)nSelectedGenomes)*(((double)nSelectedGenomes)/(double)nTotalUnits);
    			vsParent[i].dAccumulatedNormalizedFitness = dTmpAccumulatedFitness;
    			break;
    		case NORM_EQUAL:	//chance to be picked is equal for all genomes
    			vsParent[i].dNormalizedFitness = 1.0/nSelectedGenomes;
    			vsParent[i].dAccumulatedNormalizedFitness = dTmpAccumulatedFitness;
    			break;

	        default:
	            std::cout << "Unknown normalization type" << std::endl;
	            break;
	    }
		dTmpAccumulatedFitness += vsParent[i].dNormalizedFitness;
	}


	return vsParent;
}

MutationChance Evolver::SetMutationChance(rapidxml::xml_node<>* node ){
	MutationChance sMutationChance;

	sMutationChance.dBitString = 0;
	if(node->first_node("BitString")){
		rapidxml::xml_node<>* BitStringNode = node->first_node("BitString");
		if(BitStringNode->first_attribute("allowed")){
			BitStringNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dBitString = atof(BitStringNode->value()) : sMutationChance.dBitString = 0;
		}
	}

	sMutationChance.dFlipBits = 0;
	if(node->first_node("FlipBits")){
		rapidxml::xml_node<>* FlipBitsNode = node->first_node("FlipBits");
		if(FlipBitsNode->first_attribute("allowed")){
			FlipBitsNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dFlipBits = atof(FlipBitsNode->value()) : sMutationChance.dFlipBits = 0;
		}
	}

	sMutationChance.dBoundary = 0;
	if(node->first_node("Boundary")){
		rapidxml::xml_node<>* BoundaryNode = node->first_node("Boundary");
		if(BoundaryNode->first_attribute("allowed")){
			BoundaryNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dBoundary = atof(BoundaryNode->value()) : sMutationChance.dBoundary = 0;
		}
	}

	sMutationChance.dUniform = 0;
	if(node->first_node("Uniform")){
		rapidxml::xml_node<>* BoundaryNode = node->first_node("Uniform");
		if(BoundaryNode->first_attribute("allowed")){
			BoundaryNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dUniform = atof(BoundaryNode->value()) : sMutationChance.dUniform = 0;
		}
	}

	sMutationChance.dGaussian = 0;
	sMutationChance.dGaussianSigma = 0;
	if(node->first_node("Gaussian")){
		rapidxml::xml_node<>* GaussianNode = node->first_node("Gaussian");
		if(GaussianNode->first_attribute("allowed")){
			GaussianNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dGaussian = atof(GaussianNode->value()) : sMutationChance.dGaussian = 0;
		}
		GaussianNode->first_attribute("sigma")?	sMutationChance.dGaussianSigma = atof(GaussianNode->first_attribute("sigma")->value()) : sMutationChance.dGaussianSigma = 1.0;
	}

	sMutationChance.dDuplication = 0;
	if(node->first_node("Duplication")){
		rapidxml::xml_node<>* DuplicationNode = node->first_node("Duplication");
		if(DuplicationNode->first_attribute("allowed")){
			DuplicationNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dDuplication = atof(DuplicationNode->value()) : sMutationChance.dDuplication = 0;
		}
	}

	sMutationChance.dDeletion = 0;
	if(node->first_node("Deletion")){
		rapidxml::xml_node<>* DeletionNode = node->first_node("Deletion");
		if(DeletionNode->first_attribute("allowed")){
			DeletionNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dDeletion = atof(DeletionNode->value()) : sMutationChance.dDeletion = 0;
		}
	}

	sMutationChance.dInsertion = 0;
	if(node->first_node("Insertion")){
		rapidxml::xml_node<>* InsertionNode = node->first_node("Insertion");
		if(InsertionNode->first_attribute("allowed")){
			InsertionNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dInsertion = atof(InsertionNode->value()) : sMutationChance.dInsertion = 0;
		}
	}

	sMutationChance.dSwap = 0;
	if(node->first_node("Swap")){
		rapidxml::xml_node<>* InsertionNode = node->first_node("Swap");
		if(InsertionNode->first_attribute("allowed")){
			InsertionNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dSwap = atof(InsertionNode->value()) : sMutationChance.dSwap = 0;
		}
	}

	sMutationChance.dGeneDuplication = 0;
	if(node->first_node("GeneDuplication")){
		rapidxml::xml_node<>* DuplicationNode = node->first_node("GeneDuplication");
		if(DuplicationNode->first_attribute("allowed")){
			DuplicationNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dGeneDuplication = atof(DuplicationNode->value()) : sMutationChance.dGeneDuplication = 0;
		}
	}

	sMutationChance.dGeneDeletion = 0;
	if(node->first_node("GeneDeletion")){
		rapidxml::xml_node<>* DeletionNode = node->first_node("GeneDeletion");
		if(DeletionNode->first_attribute("allowed")){
			DeletionNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dGeneDeletion = atof(DeletionNode->value()) : sMutationChance.dGeneDeletion = 0;
		}
	}

	sMutationChance.dGeneInsertion = 0;
	if(node->first_node("GeneInsertion")){
		rapidxml::xml_node<>* InsertionNode = node->first_node("GeneInsertion");
		if(InsertionNode->first_attribute("allowed")){
			InsertionNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dGeneInsertion = atof(InsertionNode->value()) : sMutationChance.dGeneInsertion = 0;
		}
	}

	sMutationChance.dGeneSwap = 0;
	if(node->first_node("GeneSwap")){
		rapidxml::xml_node<>* InsertionNode = node->first_node("GeneSwap");
		if(InsertionNode->first_attribute("allowed")){
			InsertionNode->first_attribute("allowed")->value() == std::string("true")?	sMutationChance.dGeneSwap = atof(InsertionNode->value()) : sMutationChance.dGeneSwap = 0;
		}
	}


	return sMutationChance;
}

MutationChance Evolver::GetMutationChance(EncodingType encodingType){

	MutationChance cMutationChance;
	switch (encodingType)
	    {
	        case ENCODING_BINARY:
	        	cMutationChance = sMutationChances.BinaryMutationChance;
	            break;

	        case ENCODING_INTEGER:
	        	cMutationChance =  sMutationChances.IntegerMutationChance;
	            break;

	        case ENCODING_DOUBLE:
	        	cMutationChance =  sMutationChances.DoubleMutationChance;
	            break;

	        case ENCODING_ALPHANUM:
	        	cMutationChance =  sMutationChances.AlphanumMutationChance;
	            break;

	        case ENCODING_CUSTOM:
	        	cMutationChance =  sMutationChances.CustomMutationChance;
	            break;

	        case ENCODING_TREE:
	        	cMutationChance =  sMutationChances.TreeMutationChance;
	            break;

	        default:
	            std::cout << "Unknown encoding type" << std::endl;
	            break;
	    }
	return cMutationChance;
}

void Evolver::RWS(std::vector<Parent> selection, Rosetta* population){

	int nLow = 0;
	int nHigh = 10000;	//5 decimals
	double dRandom = 0;

	for(int i = 0; i<m_nMaxParents; i++){
		dRandom = ((rand() % (nHigh - nLow + 1)) + nLow)/(double)nHigh;		//random number between 0 and 1, 5 decimals

		for(unsigned int j = 0; j < selection.size(); j++){
			if(selection[j].dAccumulatedNormalizedFitness + selection[j].dNormalizedFitness >= dRandom){
				//add parent to recombination
				m_cRecombination.AddParent(population[selection[j].nIndex].cGenome.GetXML());
				break;
			}

		}

	}

}
void Evolver::SUS(std::vector<Parent> selection, Rosetta* population){
	int nLow = 0;
	int nHigh = 10000;	//5 decimals
	double dRandom = 0;

	dRandom = ((rand() % (nHigh - nLow + 1)) + nLow)/(double)nHigh;		//random number between 0 and 1, 5 decimals

	for(int i = 0; i<m_nMaxParents; i++){

		for(unsigned int j = 0; j < selection.size(); j++){
			if(selection[j].dAccumulatedNormalizedFitness + selection[j].dNormalizedFitness >= dRandom){
				//add parent to recombination
				m_cRecombination.AddParent(population[selection[j].nIndex].cGenome.GetXML());
				break;
			}
		}

		dRandom += 1.0/(double)m_nMaxParents;
		(dRandom > 1)?dRandom -= 1:dRandom;		//if dRandom get bigger than 1, subtract 1 to make it between 0 and 1 again
	}
}
void Evolver::Tournament(std::vector<Parent> selection, Rosetta* population){

	int nLow = 0;
	int nHigh = selection.size()-1;
	int nRandom = 0;

	std::vector<int> tournament;

	for(int i = 0; i<m_nMaxParents; i++){
		tournament.clear();

		//pick m_nTournamentSize parents at random from selection and add them to the vector
		for(int j = 0; j<m_nTournamentSize; j++ ){
			nRandom = (rand() % (nHigh - nLow + 1)) + nLow;		//random number between 0 and selection.size-1
			tournament.push_back(nRandom);
		}

		//since selection is already sorted by ascending fitness, all that needs to be done is to sort the tournament vector and then add parent at the first index
		std::sort(tournament.begin(), tournament.end());
		m_cRecombination.AddParent(population[selection[tournament[0]].nIndex].cGenome.GetXML());
	}
}
