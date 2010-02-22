#include <string.h>
#include <ctype.h>

int insert_into_string(char *str, int place, int space, char *edit);
int delete_from_string(char *str, int place, int cdel);
int bkspce_from_string(char *str, int place, int cdel);

/*insert printable characters from edit into str.*/
int insert_into_string(char *str, int place, int space, char *edit){
	int ledit=0;
	while(isprint(edit[ledit]))ledit++;
	int lstr=strlen(str)+1;
	lstr-=place;
	str+=place;
	if(lstr+ledit>space)return 0;//uhoh
	memmove(str+ledit,str,lstr);//move the string forward to account for the new data
	memcpy(str,edit,ledit);//copy the new data in.
	return ledit;
}

/*Delete characters, removed forward*/
int delete_from_string(char *str, int place, int cdel){
	int lstr=strlen(str)+1;
	if(place<0||cdel>lstr-place)return 0;
	memmove(str+place,str+place+cdel,lstr-place-cdel);
	return cdel;
}

/*Delete characters, backward.*/
int bkspce_from_string(char *str, int place, int cdel){
	return delete_from_string(str,place-cdel,cdel);
}


