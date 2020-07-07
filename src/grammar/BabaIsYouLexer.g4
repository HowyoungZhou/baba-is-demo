// Baba Is You Lexer
// From Baba Is You Wiki under CC-BY-SA
// https://babaiswiki.fandom.com/wiki/Baba_Is_You_Wiki

lexer grammar BabaIsYouLexer;

// Nouns
// A
ALGAE : A L G A E;
ALL : A L L;
ANNI : A N N I;
// B
BABA : B A B A;
BAT : B A T;
BELT : B E L T;
BIRD : B I R D;
BOG : B O G;
BOLT : B O L T;
BOX : B O X;
BRICK : B R I C K;
BUBBLE : B U B B L E;
BUG : B U G;
// C
CAKE : C A K E;
CASH : C A S H;
CIRCLE : C I R C L E;
CLIFF : C L I F F;
CLOUD : C L O U D;
COG : C O G;
CRAB : C R A B;
CRYSTAL : C R Y S T A L;
CUP : C U P;
CURSOR : C U R S O R;
// D
DOOR : D O O R;
DOT : D O T;
DUST : D U S T;
// E
EMPTY : E M P T Y;
EYE : E Y E;
// F
FENCE : F E N C E;
FIRE : F I R E;
FLAG : F L A G;
FLOWER : F L O W E R;
FOLIAGE : F O L I A G E;
FOOT : F O O T;
FRUIT : F R U I T;
FUNGI : F U N G I;
FUNGUS : F U N G U S;
// G
GEM : G E M;
GHOST : G H O S T;
GRASS : G R A S S;
GROUP : G R O U P;
// H
HAND : H A N D;
HEDGE : H E D G E;
HUSK : H U S K;
HUSKS : H U S K S;
// I
ICE : I C E;
IMAGE : I M A G E;
// J
JELLY : J E L L Y;
// K
KEKE : K E K E;
KEY : K E Y;
// L
LADDER : L A D D E R;
LAVA : L A V A;
LEAF : L E A F;
LEVEL : L E V E L;
LINE : L I N E;
LOVE : L O V E;
// M
ME : M E;
MOON : M O O N;
// O
ORB : O R B;
// P
PILLAR : P I L L A R;
PIPE : P I P E;
// R
REED : R E E D;
ROBOT : R O B O T;
ROCK : R O C K;
ROCKET : R O C K E T;
ROSE : R O S E;
RUBBLE : R U B B L E;
// S
SHIRT : S H I R T;
SIGN : S I G N;
SKULL : S K U L L;
SPIKE : S P I K E;
SQUARE : S Q U A R E;
STAR : S T A R;
STATUE : S T A T U E;
STUMP : S T U M P;
SUN : S U N;
// T
TEXT : T E X T;
TILE : T I L E;
TRACK : T R A C K;
TRAIN : T R A I N;
TREE : T R E E;
TREES : T R E E S;
TRIANGLE : T R I A N G L E;
// U
UFO : U F O;
// W
WALL : W A L L;
WATER : W A T E R;
WORM : W O R M;
// Letters
A : [aA];
B : [bB];
C : [cC];
D : [dD];
E : [eE];
F : [fF];
G : [gG];
H : [hH];
I : [iI];
J : [jJ];
K : [kK];
L : [lL];
M : [mM];
N : [nN];
O : [oO];
P : [pP];
Q : [qQ];
R : [rR];
S : [sS];
T : [tT];
U : [uU];
V : [vV];
W : [wW];
X : [xX];
Y : [yY];
Z : [zZ];

// Operators
// A
ABOVE : A B O V E;
OP_AND : A N D;
// F
FACING : F A C I N G;
FEAR : F E A R;
FOLLOW : F O L L O W;
// H
HAS : H A S;
// I
IDLE : I D L E;
IS : I S;
// L
LONELY : L O N E L Y;
// M
MAKE : M A K E;
MIMIC : M I M I C;
// N
NEAR : N E A R;
OP_NOT : N O T;
// O
ON : O N;
// P
PLAY : P L A Y;
POWERED : P O W E R E D;
// S
SELDOM : S E L D O M;
// W
WITHOUT : W I T H O U T;

// Properties
// B
BACK : B A C K;
BEST : B E S T;
BONUS : B O N U S;
BROKEN : B R O K E N;
// C
CHILL : C H I L L;
CRASH : C R A S H;
// D
DEFEAT : D E F E A T;
DETURN : D E T U R N;
DONE : D O N E;
// E
END : E N D;
// F
FALL : F A L L;
P_FLOAT : F L O A T;
// H
HIDE : H I D E;
HOT : H O T;
// M
MELT : M E L T;
P_MORE : M O R E;
MOVE : M O V E;
// N
NUDGE : N U D G E;
// O
OPEN : O P E N;
// P
POWER : P O W E R;
PULL : P U L L;
PUSH : P U S H;
// S
SAD : S A D;
SAFE : S A F E;
SELECT : S E L E C T;
SHIFT : S H I F T;
SHUT : S H U T;
SINK : S I N K;
SLEEP : S L E E P;
STILL : S T I L L;
STOP : S T O P;
SWAP : S W A P;
// T
TELE : T E L E;
TURN : T U R N;
// W
WEAK : W E A K;
WIN : W I N;
WONDER : W O N D E R;
WORD : W O R D;
// Y
YOU : Y O U;
YOU2 : Y O U '2';
// Directions
UP : U P;
DOWN : D O W N;
LEFT : L E F T;
RIGHT : R I G H T;
// Colors
ROSY : R O S Y;
PINK : P I N K;
RED : R E D;
ORANGE : O R A N G E;
YELLOW : Y E L L O W;
LIME : L I M E;
GREEN : G R E E N;
CYAN : C Y A N;
BLUE : B L U E;
PURPLE : P U R P L E;
BROWN : B R O W N;
BLACK : B L A C K;
GREY : G R E Y;
SILVER : S I L V E R;
WHITE : W H I T E;

SEMICOLON : ';';

SPACES
 : [ \u000B\t\r\n] -> channel(HIDDEN)
 ;
