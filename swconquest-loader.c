/* swconquest-loader -- created by swyter -- licensed under MIT-like terms.
 * * * * * * * * * *
 * launches mount and blade with our module selected plus injecting our own font paths in memory,
 * so we don't have to hot-swap files physically.
 */

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>

main(){

	//checking if the game exists
	printf("locating mount and blade 1011: ");
	
	if(!FileExists("../../mount&blade.exe"))
		printf("[not found] ");
	else
		printf("[found] ");
	
	
	printf("\n");
  
  
	//selecting default module
	printf("selecting '%s' as default module: ", SetActiveMod());
	printf("[done]\n");
  
  
	//launching the game
	printf("launching the game: "); LaunchGame();
	printf("[done]\n");
  
  
	//injecting paths in memory
	printf("injecting paths in memory: ");
	printf("done\n");
	
	getchar();
	return 0;
}