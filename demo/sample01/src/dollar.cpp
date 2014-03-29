#include "dollar.h"

Dollar::Dollar(int amount){
	m_amount = amount;	
}

void Dollar::times(int multiplier){
	m_amount *= multiplier;	
}

