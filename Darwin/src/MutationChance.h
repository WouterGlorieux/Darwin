/*
 * MutationChance.h
 *
 *  Created on: 5-mrt.-2012
 *      Author: woutergl
 */

#ifndef MUTATIONCHANCE_H_
#define MUTATIONCHANCE_H_

class MutationChance
{
public:
	double dBitString;
	double dFlipBits;
	double dBoundary;
	double dUniform;
	double dGaussian;
	double dGaussianSigma;
	double dDuplication;
	double dDeletion;
	double dInsertion;
	double dSwap;
	double dGeneDuplication;
	double dGeneDeletion;
	double dGeneInsertion;
	double dGeneSwap;

	MutationChance()	//default constructor
	{
		dBitString = 0;
		dFlipBits = 0;
		dBoundary = 0;
		dUniform = 0;
		dGaussian = 0;
		dGaussianSigma = 0;
		dDuplication = 0;
		dDeletion = 0;
		dInsertion = 0;
		dSwap = 0;
		dGeneDuplication = 0;
		dGeneDeletion = 0;
		dGeneInsertion = 0;
		dGeneSwap = 0;
	}

	~MutationChance()	//default deconstructor
	{

	}
};

struct MutationChances
{
    MutationChance BinaryMutationChance;
    MutationChance IntegerMutationChance;
    MutationChance DoubleMutationChance;
    MutationChance AlphanumMutationChance;
    MutationChance CustomMutationChance;
    MutationChance ListMutationChance;
};

#endif /* MUTATIONCHANCE_H_ */
