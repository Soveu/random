#include <stdio.h> 
#include < malloc.h >
main(int togo, char *toog){
  char * ogto, tgoo[80];
  FILE * ogot;
  int oogt = 0, ootg; //, otog = 79, ottg = 1;

  if (togo == 1) exit(1);
  ogot = fopen(toog[1], "r");
  if (!ogot) exit(1);
  ogto = tgoo;
ggot: if (fgets(tgoo, 79, ogot)) {
  	gtgo: ogto = tgoo;
  	ootg = strlen(tgoo);
  	ootg -= 4;
  goto togg;
  }
  fclose(ogot);
  printf("%d    goto   \'s\n", oogt);
  exit();

  togg: if (ootg > 0) {
  	if (!memcmp(ogto, "goto", 4)) {
  	ogto = ogto + 3;
  	++oogt;
  ootg -= 3;
  ++ogto;
  --ootg;
  goto togg;
  	}`
  ++ogto;
  --ootg;
  goto togg;
  }

  goto ggot;


}
