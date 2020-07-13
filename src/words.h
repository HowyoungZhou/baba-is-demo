#ifndef BABA_IS_YOU_WORDS_H
#define BABA_IS_YOU_WORDS_H

enum class Words : size_t {
    ALGAE = 1,
    ALL = 2,
    ANNI = 3,
    BABA = 4,
    BAT = 5,
    BELT = 6,
    BIRD = 7,
    BOG = 8,
    BOLT = 9,
    BOX = 10,
    BRICK = 11,
    BUBBLE = 12,
    BUG = 13,
    CAKE = 14,
    CASH = 15,
    CIRCLE = 16,
    CLIFF = 17,
    CLOUD = 18,
    COG = 19,
    CRAB = 20,
    CRYSTAL = 21,
    CUP = 22,
    CURSOR = 23,
    DOOR = 24,
    DOT = 25,
    DUST = 26,
    EMPTY = 27,
    EYE = 28,
    FENCE = 29,
    FIRE = 30,
    FLAG = 31,
    FLOWER = 32,
    FOLIAGE = 33,
    FOOT = 34,
    FRUIT = 35,
    FUNGI = 36,
    FUNGUS = 37,
    GEM = 38,
    GHOST = 39,
    GRASS = 40,
    GROUP = 41,
    HAND = 42,
    HEDGE = 43,
    HUSK = 44,
    HUSKS = 45,
    ICE = 46,
    IMAGE = 47,
    JELLY = 48,
    KEKE = 49,
    KEY = 50,
    LADDER = 51,
    LAVA = 52,
    LEAF = 53,
    LEVEL = 54,
    LINE = 55,
    LOVE = 56,
    ME = 57,
    MOON = 58,
    ORB = 59,
    PILLAR = 60,
    PIPE = 61,
    REED = 62,
    ROBOT = 63,
    ROCK = 64,
    ROCKET = 65,
    ROSE = 66,
    RUBBLE = 67,
    SHIRT = 68,
    SIGN = 69,
    SKULL = 70,
    SPIKE = 71,
    SQUARE = 72,
    STAR = 73,
    STATUE = 74,
    STUMP = 75,
    SUN = 76,
    TEXT = 77,
    TILE = 78,
    TRACK = 79,
    TRAIN = 80,
    TREE = 81,
    TREES = 82,
    TRIANGLE = 83,
    UFO = 84,
    WALL = 85,
    WATER = 86,
    WORM = 87,
    A = 88,
    B = 89,
    C = 90,
    D = 91,
    E = 92,
    F = 93,
    G = 94,
    H = 95,
    I = 96,
    J = 97,
    K = 98,
    L = 99,
    M = 100,
    N = 101,
    O = 102,
    P = 103,
    Q = 104,
    R = 105,
    S = 106,
    T = 107,
    U = 108,
    V = 109,
    W = 110,
    X = 111,
    Y = 112,
    Z = 113,
    ABOVE = 114,
    AND = 115,
    FACING = 116,
    FEAR = 117,
    FOLLOW = 118,
    HAS = 119,
    IDLE = 120,
    IS = 121,
    LONELY = 122,
    MAKE = 123,
    MIMIC = 124,
    NEAR = 125,
    NOT = 126,
    ON = 127,
    PLAY = 128,
    POWERED = 129,
    SELDOM = 130,
    WITHOUT = 131,
    BACK = 132,
    BEST = 133,
    BONUS = 134,
    BROKEN = 135,
    CHILL = 136,
    CRASH = 137,
    DEFEAT = 138,
    DETURN = 139,
    DONE = 140,
    END = 141,
    FALL = 142,
    FLOAT = 143,
    HIDE = 144,
    HOT = 145,
    MELT = 146,
    MORE = 147,
    MOVE = 148,
    NUDGE = 149,
    OPEN = 150,
    POWER = 151,
    PULL = 152,
    PUSH = 153,
    SAD = 154,
    SAFE = 155,
    SELECT = 156,
    SHIFT = 157,
    SHUT = 158,
    SINK = 159,
    SLEEP = 160,
    STILL = 161,
    STOP = 162,
    SWAP = 163,
    TELE = 164,
    TURN = 165,
    WEAK = 166,
    WIN = 167,
    WONDER = 168,
    WORD = 169,
    YOU = 170,
    YOU2 = 171,
    UP = 172,
    DOWN = 173,
    LEFT = 174,
    RIGHT = 175,
    ROSY = 176,
    PINK = 177,
    RED = 178,
    ORANGE = 179,
    YELLOW = 180,
    LIME = 181,
    GREEN = 182,
    CYAN = 183,
    BLUE = 184,
    PURPLE = 185,
    BROWN = 186,
    BLACK = 187,
    GREY = 188,
    SILVER = 189,
    WHITE = 190,
};

static const char *kWordsHintString = "ALGAE,ALL,ANNI,BABA,BAT,BELT,BIRD,BOG,BOLT,BOX,BRICK,BUBBLE,BUG,CAKE,CASH,CIRCLE,CLIFF,CLOUD,COG,CRAB,CRYSTAL,CUP,CURSOR,DOOR,DOT,DUST,EMPTY,EYE,FENCE,FIRE,FLAG,FLOWER,FOLIAGE,FOOT,FRUIT,FUNGI,FUNGUS,GEM,GHOST,GRASS,GROUP,HAND,HEDGE,HUSK,HUSKS,ICE,IMAGE,JELLY,KEKE,KEY,LADDER,LAVA,LEAF,LEVEL,LINE,LOVE,ME,MOON,ORB,PILLAR,PIPE,REED,ROBOT,ROCK,ROCKET,ROSE,RUBBLE,SHIRT,SIGN,SKULL,SPIKE,SQUARE,STAR,STATUE,STUMP,SUN,TEXT,TILE,TRACK,TRAIN,TREE,TREES,TRIANGLE,UFO,WALL,WATER,WORM,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,ABOVE,AND,FACING,FEAR,FOLLOW,HAS,IDLE,IS,LONELY,MAKE,MIMIC,NEAR,NOT,ON,PLAY,POWERED,SELDOM,WITHOUT,BACK,BEST,BONUS,BROKEN,CHILL,CRASH,DEFEAT,DETURN,DONE,END,FALL,FLOAT,HIDE,HOT,MELT,MORE,MOVE,NUDGE,OPEN,POWER,PULL,PUSH,SAD,SAFE,SELECT,SHIFT,SHUT,SINK,SLEEP,STILL,STOP,SWAP,TELE,TURN,WEAK,WIN,WONDER,WORD,YOU,YOU2,UP,DOWN,LEFT,RIGHT,ROSY,PINK,RED,ORANGE,YELLOW,LIME,GREEN,CYAN,BLUE,PURPLE,BROWN,BLACK,GREY,SILVER,WHITE";

enum class Nouns : size_t {
    ALGAE = 1,
    ALL = 2,
    ANNI = 3,
    BABA = 4,
    BAT = 5,
    BELT = 6,
    BIRD = 7,
    BOG = 8,
    BOLT = 9,
    BOX = 10,
    BRICK = 11,
    BUBBLE = 12,
    BUG = 13,
    CAKE = 14,
    CASH = 15,
    CIRCLE = 16,
    CLIFF = 17,
    CLOUD = 18,
    COG = 19,
    CRAB = 20,
    CRYSTAL = 21,
    CUP = 22,
    CURSOR = 23,
    DOOR = 24,
    DOT = 25,
    DUST = 26,
    EMPTY = 27,
    EYE = 28,
    FENCE = 29,
    FIRE = 30,
    FLAG = 31,
    FLOWER = 32,
    FOLIAGE = 33,
    FOOT = 34,
    FRUIT = 35,
    FUNGI = 36,
    FUNGUS = 37,
    GEM = 38,
    GHOST = 39,
    GRASS = 40,
    GROUP = 41,
    HAND = 42,
    HEDGE = 43,
    HUSK = 44,
    HUSKS = 45,
    ICE = 46,
    IMAGE = 47,
    JELLY = 48,
    KEKE = 49,
    KEY = 50,
    LADDER = 51,
    LAVA = 52,
    LEAF = 53,
    LEVEL = 54,
    LINE = 55,
    LOVE = 56,
    ME = 57,
    MOON = 58,
    ORB = 59,
    PILLAR = 60,
    PIPE = 61,
    REED = 62,
    ROBOT = 63,
    ROCK = 64,
    ROCKET = 65,
    ROSE = 66,
    RUBBLE = 67,
    SHIRT = 68,
    SIGN = 69,
    SKULL = 70,
    SPIKE = 71,
    SQUARE = 72,
    STAR = 73,
    STATUE = 74,
    STUMP = 75,
    SUN = 76,
    TEXT = 77,
    TILE = 78,
    TRACK = 79,
    TRAIN = 80,
    TREE = 81,
    TREES = 82,
    TRIANGLE = 83,
    UFO = 84,
    WALL = 85,
    WATER = 86,
    WORM = 87,
    A = 88,
    B = 89,
    C = 90,
    D = 91,
    E = 92,
    F = 93,
    G = 94,
    H = 95,
    I = 96,
    J = 97,
    K = 98,
    L = 99,
    M = 100,
    N = 101,
    O = 102,
    P = 103,
    Q = 104,
    R = 105,
    S = 106,
    T = 107,
    U = 108,
    V = 109,
    W = 110,
    X = 111,
    Y = 112,
    Z = 113,
};

static const char *kNounsHintString = "ALGAE,ALL,ANNI,BABA,BAT,BELT,BIRD,BOG,BOLT,BOX,BRICK,BUBBLE,BUG,CAKE,CASH,CIRCLE,CLIFF,CLOUD,COG,CRAB,CRYSTAL,CUP,CURSOR,DOOR,DOT,DUST,EMPTY,EYE,FENCE,FIRE,FLAG,FLOWER,FOLIAGE,FOOT,FRUIT,FUNGI,FUNGUS,GEM,GHOST,GRASS,GROUP,HAND,HEDGE,HUSK,HUSKS,ICE,IMAGE,JELLY,KEKE,KEY,LADDER,LAVA,LEAF,LEVEL,LINE,LOVE,ME,MOON,ORB,PILLAR,PIPE,REED,ROBOT,ROCK,ROCKET,ROSE,RUBBLE,SHIRT,SIGN,SKULL,SPIKE,SQUARE,STAR,STATUE,STUMP,SUN,TEXT,TILE,TRACK,TRAIN,TREE,TREES,TRIANGLE,UFO,WALL,WATER,WORM,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z";

enum class Operators : size_t {
    ABOVE = 114,
    AND = 115,
    FACING = 116,
    FEAR = 117,
    FOLLOW = 118,
    HAS = 119,
    IDLE = 120,
    IS = 121,
    LONELY = 122,
    MAKE = 123,
    MIMIC = 124,
    NEAR = 125,
    NOT = 126,
    ON = 127,
    PLAY = 128,
    POWERED = 129,
    SELDOM = 130,
    WITHOUT = 131,
};

static const char *kOperatorsHintString = "ABOVE,AND,FACING,FEAR,FOLLOW,HAS,IDLE,IS,LONELY,MAKE,MIMIC,NEAR,NOT,ON,PLAY,POWERED,SELDOM,WITHOUT";

enum class Properties : size_t {
    BACK = 132,
    BEST = 133,
    BONUS = 134,
    BROKEN = 135,
    CHILL = 136,
    CRASH = 137,
    DEFEAT = 138,
    DETURN = 139,
    DONE = 140,
    END = 141,
    FALL = 142,
    FLOAT = 143,
    HIDE = 144,
    HOT = 145,
    MELT = 146,
    MORE = 147,
    MOVE = 148,
    NUDGE = 149,
    OPEN = 150,
    POWER = 151,
    PULL = 152,
    PUSH = 153,
    SAD = 154,
    SAFE = 155,
    SELECT = 156,
    SHIFT = 157,
    SHUT = 158,
    SINK = 159,
    SLEEP = 160,
    STILL = 161,
    STOP = 162,
    SWAP = 163,
    TELE = 164,
    TURN = 165,
    WEAK = 166,
    WIN = 167,
    WONDER = 168,
    WORD = 169,
    YOU = 170,
    YOU2 = 171,
    UP = 172,
    DOWN = 173,
    LEFT = 174,
    RIGHT = 175,
    ROSY = 176,
    PINK = 177,
    RED = 178,
    ORANGE = 179,
    YELLOW = 180,
    LIME = 181,
    GREEN = 182,
    CYAN = 183,
    BLUE = 184,
    PURPLE = 185,
    BROWN = 186,
    BLACK = 187,
    GREY = 188,
    SILVER = 189,
    WHITE = 190,
};

static const char *kPropertiesHintString = "BACK,BEST,BONUS,BROKEN,CHILL,CRASH,DEFEAT,DETURN,DONE,END,FALL,FLOAT,HIDE,HOT,MELT,MORE,MOVE,NUDGE,OPEN,POWER,PULL,PUSH,SAD,SAFE,SELECT,SHIFT,SHUT,SINK,SLEEP,STILL,STOP,SWAP,TELE,TURN,WEAK,WIN,WONDER,WORD,YOU,YOU2,UP,DOWN,LEFT,RIGHT,ROSY,PINK,RED,ORANGE,YELLOW,LIME,GREEN,CYAN,BLUE,PURPLE,BROWN,BLACK,GREY,SILVER,WHITE";

enum class Directions : size_t {
    UP = 172,
    DOWN = 173,
    LEFT = 174,
    RIGHT = 175,
};

static const char *kDirectionsHintString = "UP,DOWN,LEFT,RIGHT";

#endif // BABA_IS_YOU_WORDS_H
