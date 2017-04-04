#include "Main.h"
#include"cuSDStruct.h"
#include"Debugger.h"
#include<map>

const struct PaperIdWrapper_Scheme const_PaperIdWrapper_Scheme;

std::map<decltype(const_PaperIdWrapper_Scheme.classPtr), decltype(const_PaperIdWrapper_Scheme.paper_id)> debugcopy_data;
size_t debugcopy_size;

void copy_data(struct PaperIdWrapper_Scheme * original_paperIdWrapperScheme, size_t size) {
	size_t i;
	decltype(debugcopy_data)::iterator it;
	
	debugcopy_size = size;
	printf("-------copy-------\n");
	for (i = 0; i < debugcopy_size; i++) {
		debugcopy_data.insert(std::make_pair(original_paperIdWrapperScheme[i].classPtr, original_paperIdWrapperScheme[i].paper_id));
		if ((it = debugcopy_data.find(original_paperIdWrapperScheme[i].classPtr)) != debugcopy_data.end()) {
			printf(" %llu %d\n", original_paperIdWrapperScheme[i].classPtr, original_paperIdWrapperScheme[i].paper_id);
			continue;
			if (it->second != original_paperIdWrapperScheme[i].paper_id) {
				printf_stream(stdout, "This should not happen (in copy_data) \n %d %d not same \n",
					original_paperIdWrapperScheme[i].paper_id,
					it->second
				);
			}
		}
	}

}

void check_data(struct PaperIdWrapper_Scheme * check_paperIdWrapperScheme) 
{
	size_t i;
	decltype(debugcopy_data)::iterator it;

	printf("-------check-------\n");
	for (i = 0; i < debugcopy_size; i++) {
		if ((it = debugcopy_data.find(check_paperIdWrapperScheme[i].classPtr)) != debugcopy_data.end()) {
			printf(" %llu %d\n", check_paperIdWrapperScheme[i].classPtr, check_paperIdWrapperScheme[i].paper_id);
			continue;
			if (it->second != check_paperIdWrapperScheme[i].paper_id) {
				printf_stream(stdout, "This should not happen (in check_data) \n %d %d not same \n",
						check_paperIdWrapperScheme[i].paper_id,
						it->second
					);
			}
		}
	}
}

void remove_data() {
	debugcopy_data.clear();
}

