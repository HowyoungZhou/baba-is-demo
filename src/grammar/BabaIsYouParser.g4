parser grammar BabaIsYouParser;

options { tokenVocab=BabaIsYouLexer; }

exprs: expr (SEMICOLON expr)* SEMICOLON*;

expr
 : OP_NOT? LONELY expr # LonelyCondition
 | OP_NOT expr # NotExpr
 | expr OP_AND expr # AndExpr
 | expr OP_AND? OP_NOT? (ON | NEAR | FACING) expr # Condition
 | <assoc=right> expr (IS | HAS | MAKE) OP_NOT? expr # Verb
 | expr OP_AND (IS | HAS | MAKE) OP_NOT? expr # ConjunctVerb
 | noun # NounLiteral
 | property # PropertyLiteral
 ;

noun
 : ALGAE
 | ALL
 | ANNI
 | BABA
 | BAT
 | BELT
 | BIRD
 | BOG
 | BOLT
 | BOX
 | BRICK
 | BUBBLE
 | BUG
 | CAKE
 | CASH
 | CIRCLE
 | CLIFF
 | CLOUD
 | COG
 | CRAB
 | CRYSTAL
 | CUP
 | CURSOR
 | DOOR
 | DOT
 | DUST
 | EMPTY
 | EYE
 | FENCE
 | FIRE
 | FLAG
 | FLOWER
 | FOLIAGE
 | FOOT
 | FRUIT
 | FUNGI
 | FUNGUS
 | GEM
 | GHOST
 | GRASS
 | GROUP
 | HAND
 | HEDGE
 | HUSK
 | HUSKS
 | ICE
 | IMAGE
 | JELLY
 | KEKE
 | KEY
 | LADDER
 | LAVA
 | LEAF
 | LEVEL
 | LINE
 | LOVE
 | ME
 | MOON
 | ORB
 | PILLAR
 | PIPE
 | REED
 | ROBOT
 | ROCK
 | ROCKET
 | ROSE
 | RUBBLE
 | SHIRT
 | SIGN
 | SKULL
 | SPIKE
 | SQUARE
 | STAR
 | STATUE
 | STUMP
 | SUN
 | TEXT
 | TILE
 | TRACK
 | TRAIN
 | TREE
 | TREES
 | TRIANGLE
 | UFO
 | WALL
 | WATER
 | WORM
 | A
 | B
 | C
 | D
 | E
 | F
 | G
 | H
 | I
 | J
 | K
 | L
 | M
 | N
 | O
 | P
 | Q
 | R
 | S
 | T
 | U
 | V
 | W
 | X
 | Y
 | Z;

property
 : BACK
 | BEST
 | BONUS
 | BROKEN
 | CHILL
 | CRASH
 | DEFEAT
 | DETURN
 | DONE
 | END
 | FALL
 | P_FLOAT
 | HIDE
 | HOT
 | MELT
 | P_MORE
 | MOVE
 | NUDGE
 | OPEN
 | POWER
 | PULL
 | PUSH
 | SAD
 | SAFE
 | SELECT
 | SHIFT
 | SHUT
 | SINK
 | SLEEP
 | STILL
 | STOP
 | SWAP
 | TELE
 | TURN
 | WEAK
 | WIN
 | WONDER
 | WORD
 | YOU
 | YOU2
 | UP
 | DOWN
 | LEFT
 | RIGHT
 | ROSY
 | PINK
 | RED
 | ORANGE
 | YELLOW
 | LIME
 | GREEN
 | CYAN
 | BLUE
 | PURPLE
 | BROWN
 | BLACK
 | GREY
 | SILVER
 | WHITE;
