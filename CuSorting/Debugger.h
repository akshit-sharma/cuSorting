#pragma once

#include "cuSDStruct.h"

#define print_debug_specific \
printf("from cpu \n paper id %d \n classPtr is %llu \n paper id in classPtr is %d \n",		\
paperIdWrapper[14].paper_id,																\
paperIdWrapper[14].classPtr,																\
static_cast<SchemeDataStructure *>(paperIdWrapper[14].classPtr)->getPaperId()				\
);																							\
printf("paper id %d \n classPtr is %llu \n paper id in classPtr is %d \n",					\
	paperIdWrapper[15].paper_id,															\
	paperIdWrapper[15].classPtr,															\
	static_cast<SchemeDataStructure *>(paperIdWrapper[15].classPtr)->getPaperId()			\
);																							\
printf("paper id %d \n classPtr is %llu \n paper id in classPtr is %d \n",					\
	paperIdWrapper[16].paper_id,															\
	paperIdWrapper[16].classPtr,															\
	static_cast<SchemeDataStructure *>(paperIdWrapper[16].classPtr)->getPaperId()			\
);																							

void copy_data(struct PaperIdWrapper_Scheme * original_paperIdWrapperScheme, size_t size);
void check_data(struct PaperIdWrapper_Scheme * check_paperIdWrapperScheme);
void remove_data();
