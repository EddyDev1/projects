/*
    Project - Markov

    model.h

    Class declaration for markov_model (abstract base class for Markov model
    classes).
*/

#ifndef _MODEL_H
#define _MODEL_H

#include <string>

class markov_model {
public:
	// give the model the example text and the model order; the model
	// should do any preprocessing in this call
	virtual void initialize(std::string text, int order) = 0;

	// produce a text in the style of the example
	virtual std::string generate(int size) = 0;
};

#endif

