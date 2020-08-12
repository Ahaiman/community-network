/*
 * algo_3.c
 *
 *  Created on: 11 баев„ 2020
 *      Author: Avital
 */


Stack *findCommunities(){
	Stack *P;
	Stack *O;
	Group *g;

	/*P */
//	1.Start with a trivial division into one group: P   ff1; : : : ; ngg

	/*O*/
	O = allocate_stack();

	while(!P -> isEmpty()){
		g = P.remove();

		/* Divide g into g1; g2 with Algorithm 2 */
		{g1, g2}  = algorithm2(g);

		/*Implenet optimiztiom */

		/* if either g1 or g2 is of size 0: Add g to O*/
		if(g1.size == 0 || g2.size == 0){
			O.add(g);
		}

		/*Add to O: any group (g1 and/or g2) of size 1*/
		if(g1.size == 1){
			O.add(g1);
		}
		else{
			P.add(g1);
		}

		if(g2.size == 1){
			O.add(g2);
		}
		else{
			P.add(g2);
		}
	}

	return O;

}
