#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
bool wcr_is_code(const char *file_name){
	return true; //todo
}

int wcr_split_file(const char* full_file_path)
{
	printf("splitting %s\n",full_file_path);
	return 0;
}

/*
scan specified folder, return 0 for success ,negative for failure,positive
*/
int wcr_scan_folder(const char *folder_name)
{
	DIR * dir;
	struct dirent *ent;
	dir = opendir(folder_name);
	char buffer[PATH_MAX];
	if(dir == NULL){
		printf("failed to open folder %s\n",folder_name);
		return -1;
	}
	while( (ent = readdir(dir)) != NULL){
		printf("%s\n",ent-> d_name);
		if(ent->d_type == DT_DIR){
			if(strcmp(ent->d_name,".") == 0 
				|| strcmp(ent->d_name,"..") == 0)
				continue;
				snprintf(buffer,sizeof(buffer),"%s\%s",folder_name,ent->d_name);
				wcr_scan_folder(buffer);
		}else{
			if(wcr_is_code(ent->d_name)){
				snprintf(buffer,sizeof(buffer),"%s\%s",folder_name,ent->d_name);
				wcr_split_file(buffer);
			}
		}
	};
	
	closedir(dir);
	return 0;	
}

int useage(const char* msg)
{
	printf("%s\n",msg);
	return -1;
}
int main(int argc, char* argv[]){
	if(argc<2){
		return useage("missing root folder");
	}
	return wcr_scan_folder(argv[1]);
}


