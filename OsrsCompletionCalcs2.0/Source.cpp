#include <iostream>
#include <random>
#include <time.h>
#include <queue>
#include <math.h>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>

// item prices, in future it would be nice to have these dynamically update to current prices, until then here is a list of static prices
const double ARMADYLHELM = 5342883, ARMADYLCHEST = 38562165, ARMADYLSKIRT = 35405545, ARMADYLHILT = 9292008, GODSHARD1 = 153985, GODSHARD2 = 150637, GODSHARD3 = 150553, ARMADYLSTANDARD = -36000,
WHIP = 2755566, ABBYDAGGER = 4953764, ABBYBLUDGEON = 40015138, SIRESTANDARD = 21000,
BURNTPAGE = 2943, TOMEFIRE = 767835, WINTERTODTSTANDARD = 10000,
MAGICFANG = 4069754, TANZFANG = 4072155, SERPVISAGE = 4083663, ONYX = 2128594, ZULRAHSTANDARD = 90400,
ZERKRING = 2239693, WARRIORRING = 42536, ARCHERRING = 4573745, SEERCULL = 14272, SEERRING = 292621, MUDSTAFF = 24215, REXSTANDARD = 9000, PRIMESTANDARD = 15500, SUPREMESTANDARD = 13000,
ARCANE = 158500000, SPECTRAL = 68300000, ELYSIAN = 931100000, CORPSTANDARD = 125000,
SKELETALVISAGE = 21966094, DRACONICVISAGE = 4107409, VORKSTANDARD = 128500,
DRAGONKNIFE = 1269000, DRAGONAXE = 288000, HYDRACLAW = 70000000, HYDRALEATHER = 5956000, HYDRATAIL = 66800, BRIMSTONERING = 3123708, HYDRASTANDARD = 122000,
TYRANNICALRING = 1631333, DRAGONPICK = 4891719, CALLISTOSTANDARD = 61000,
ETERNALCRYSTAL = 2745784, PEGASIANCRYSTAL = 99224, PRIMORDIALCRYSTAL = 32508102, SMOULDERINGSTONE = 1604872, CERBSTANDARD = 21000,
INQHELM = 293503190, INQPLATE = 432550074, INQLEGS = 566267998, INQMACE = 991610468, NIGHTMARESTAFF = 38353702, HARMORB = 1621556274, VOLORB = 358290240, ELDORB = 143123071, NIGHTMARESTANDARD = -20000,
TWISTEDBOW = 1181075132, TWISTEDBUCKLER = 3988878, KODAIINSIGNIA = 78944318, ELDERMAUL = 11921759, ANCESTHAT = 12648447, ANCESTTOP = 68171323, ANCESTLEGS = 81651269, DEXSCROLL = 26131442,
ARCANESCROLL = 1333197, DRAGONHUNTERCBOW = 97488396, DRAGONCLAWS = 60218580, BULWARK = 4158230, COXSTANDARD = 488109,
JUSTICIARHELM = 25480922, JUSTICIARPLATE = 10858504, JUSTICIARLEGS = 14821837, AVERNICHILT = 57483912, GHRAZIRAPIER = 158935037, VITURSCYTHE = 837527690, SANGSTAFF = 135162312, TOBSTANDARD = 340888,
BLADESAELDOR = 113715941, CRYSTALARMOR = 3758709, CRYSTALWEP = 190000, CORRUPTGAUNTSTANDARD = 258395,
CHAOSELESTANDARD = 28000, JADSTANDARD = -500000, SARACHNISSTANDARD = 31000, BLACKCHIN = 2892, WOODCUTSTANDARD = -127,  // WC assumes crystal axe buying crystal shards through crystal trees
SCORPIASTANDARD = 5000, SKOTIZOSTANDARD = 166600, FISHINGSTANDARD = -127, //Fish assumes crystal harpoon and buying crystal shards through crystal trees
ARMADYLCBOW = 25910757, SARAHILT = 41100000, SARASWORD = 444111, SARALIGHT = 401901, ZILYSTANDARD = 25000,
BANDOSBOOTS = 180556, BANDOSTASSY = 28435105, BANDOSCHEST = 19874956, BANDOSHILT = 10500000, BANDOSSTANDARD = 20000,
DRAGONCHAIN = 288714, OCCULTNECKLACE = 452207, SMOKESTAFF = 1659150, THERMYSTANDARD = 14000,
TREASONOUSRING = 329413, VENENATISSTANDARD = 69500, RINGOFGODS = 21554280, VETIONSTANDARD = 64000,
ZALCANOSTANDARD = 105000, MININGSTANDARD = 457, // Mine is gem rocks, assumed crystal pick(-127/rock) and gem rocks worth 584/rock.
MAHOGANYSEED = -2476, FRUITSEED = -169672, MAGICSEED = -114118, REDWOODSEED = -31520, CRYSTALSEED = -191833, CALQSEED = -133,
HERBISTANDARD = 7000, BAHIGHGAMBLE = 96954, ZUKSTANDARD = -1000000, MOLESTANDARD = 23648,
GROTGUARDSTANDARD = 48000, GRANITEHAMMER = 313123, TOURMALINECORE = 3453000, KQSTANDARD = 50000, KBDSTANDARD = 18000, KRAKENSTANDARD = 15000, TRIDENT = 842311, TENTACLE = 467719,
ZAMMYSTANDARD = 14000, ZAMMYSPEAR = 16720591, STEAMSTAFF = 91360, ZAMMYHILT = 4287908, STAFFOFDEAD = 4526198;


struct thirdAgeBox
{
	int hardClues;
	int eliteClues;
	int masterClues;
	long int time;
};

bool operator<(thirdAgeBox a, thirdAgeBox b)
{
	return a.time < b.time;
}

bool operator==(thirdAgeBox a, thirdAgeBox b)
{
	return a.time == b.time;
}

struct petBox
{
	double time;
	double petDropRate;
	double worstRate;
	double bestRate;
	double finishedGp;
	double finishedBonusElites;
	double finishedGpBeforeHound;
};

bool operator<(petBox a, petBox b)
{
	return a.time < b.time;
}

bool operator==(petBox a, petBox b)
{
	return a.time == b.time;
}

struct itemBox
{
	std::string itemName;
	int amount;
};

struct clueBox
{
	double return1;
	double return2 = 0;
	double return3 = 0;
};

struct dagBox
{
	double rex1;
	double supreme1;
	double prime1;
	double gp = 0;
	double clue = 0;
};



int barrows(int option); // 0 means not to print, 1 means to print out results of each piece
clueBox hardClues(int option);
clueBox armadyl(int option, bool petOnly);
clueBox abyssalSire(int option, bool petOnly);
clueBox wintertodt(int option, bool petOnly);
int bryophyta(int option);
clueBox zulrah(int option, bool petOnly);
dagBox dags(int option, bool petOnly);
clueBox corp(int option, bool petOnly);
clueBox vorkath(int option, bool petOnly);
int beginnerClue(int option);
clueBox easyClue(int option);
clueBox mediumClue(int option);
clueBox eliteClue(int option);
clueBox masterClue(int option, bool petOnly);
int fishingTrawler(int option);
clueBox alchemicalHydra(int option, bool petOnly);
clueBox callisto(int option, bool petOnly);
clueBox cerberus(int option, bool petOnly);
clueBox gauntlet(int option, bool petOnly); // corrupted gauntlet
int chaosFanatic(int option, bool petOnly);
clueBox chaosEle(int option);
clueBox zily(int option, bool petOnly);
clueBox jad(int option); // assumes on task and trading in cape after every cave if don't get pet
clueBox graardor(int option, bool petOnly);
clueBox mole(int option);
clueBox grotGuardians(int option, bool petOnly);
clueBox kalphiteQueen(int option, bool petOnly);
clueBox kbd(int option, bool petOnly);
clueBox kraken(int option, bool petOnly);
clueBox kril(int option, bool petOnly);
clueBox nightmare(int option, bool petOnly);
clueBox sarachnis(int option, bool petOnly);
clueBox scorpia(int option, bool petOnly);
clueBox skotizo(int option, bool petOnly);
clueBox thermy(int option, bool petOnly);
clueBox venenatis(int option, bool petOnly);
clueBox vetion(int option, bool petOnly);
clueBox zalcano(int option, bool petOnly);
thirdAgeBox efficientThirdAge(int option);
clueBox challengeXericSolo(int option, bool petOnly);
clueBox theater(int option, bool petOnly);
clueBox chinchompa(int option);
clueBox beaver(int option);
int squirrel(int option);
clueBox heron(int option);
int rift(int option);
clueBox golem(int option);
int rocky(int option);
clueBox tangle(int option);
int chompy(int option);
clueBox herbi(int option);
clueBox penance(int option);
clueBox zuk(int option);
petBox petRun(int option, bool talk);
thirdAgeBox efficientThirdAgeTwo(int option);
clueBox hardCluesBloodhound(int option);

int main()
{
	srand(time(NULL));
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 mt_rand(seed);

	int retry = -1;

	while (retry != 0)
	{
		if (retry == 1)
			barrows(1);
		else if (retry == 2)
		{
			int avg = 0;
			for (int i = 0; i < 25000; i++)
				avg += barrows(0);
			std::cout << "Average killcount to finish barrows: " << avg / 25000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				int finished = barrows(0);
				finishedSet.push(finished);
			}
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median finished killcount was: " << finishedSet.top() << '\n';
		}
		else if (retry == 3)
			hardClues(1);
		else if (retry == 4)
		{
			long long avg = 0;
			std::priority_queue<int> finishedSet;
			std::priority_queue<int> finishedGilded;
			std::priority_queue<int> finishedThirdAge;
			const int TRIALS = 10000;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox finished = hardClues(0);
				avg += finished.return1;
				finishedSet.push(finished.return1);
				finishedGilded.push(finished.return3);
				finishedThirdAge.push(finished.return2);
			}
			std::cout << "Average hard clues required to finish them: " << avg / TRIALS << '\n';
			std::cout << "The best finished hard clue count was: " << finishedSet.top() << '\n';
			std::cout << "The person with the most amount of gilded rolls got " << finishedGilded.top() << '\n';
			std::cout << "The person with the most amount of third age rolls got " << finishedThirdAge.top() << '\n';
			for (int i = 0; i < TRIALS/2; i++)
			{
				finishedSet.pop();
				finishedGilded.pop();
				finishedThirdAge.pop();
			}
			std::cout << "The medoam finished hard clue count was: " << finishedSet.top() << '\n';
			std::cout << "The person with the median of gilded rolls got " << finishedGilded.top() << '\n';
			std::cout << "The person with the median of third age rolls got " << finishedThirdAge.top() << '\n';
			for (int i = 0; i < TRIALS/2 - 1; i++)
			{
				finishedSet.pop();
				finishedGilded.pop();
				finishedThirdAge.pop();
			}
			std::cout << "The worst finished hard clue count was: " << finishedSet.top() << '\n';
			std::cout << "The person with the least amount of gilded rolls got " << finishedGilded.top() << '\n';
			std::cout << "The person with the least amount of third age rolls got " << finishedThirdAge.top() << '\n';
		}
		else if (retry == 5)
			armadyl(1, 0);
		else if (retry == 6)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			const int TRIALS = 25000;
			for (int i = 0; i < TRIALS; i++) // sort as being populated
			{
				clueBox holder = armadyl(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The most kills it took to finish armadyl was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The average killcount to finish armadyl was: " << avg / TRIALS << '\n';
			std::cout << "The median killcount to finish armadyl was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The lowest killcount to finish armadyl was: " << finishedSet.top() << '\n';
		}
		else if (retry == 7)
			wintertodt(1, 0);
		else if (retry == 8)
		{
			int avg = 0;
			std::cout << "The average killcount to finish wintertodt was: " << avg / 25000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				clueBox holder = wintertodt(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The mean killcount to finish wintertodt was: " << finishedSet.top() << '\n';
		}
		else if (retry == 9)
			abyssalSire(1, 0);
		else if (retry == 10)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++) // sort as being populated
			{
				clueBox holder = abyssalSire(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to finish abyssal sire was: " << avg / TRIALS << '\n';
			std::cout << "The highest killcount to finish abyssal sire was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The mean killcount to finish abyssal sire was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The mean killcount to finish abyssal sire was: " << finishedSet.top() << '\n';
		}
		else if (retry == 11)
			bryophyta(1);
		else if (retry == 12)
		{
			int avg = 0;
			for (int i = 0; i < 25000; i++)
				avg += bryophyta(0);
			std::cout << "The average killcount to finish bryophyta was: " << avg / 25000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				int finished = bryophyta(0);
				finishedSet.push(finished);
			}
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The mean killcount to finish bryophyta was: " << finishedSet.top() << '\n';
		}
		else if (retry == 13)
			zulrah(1, 0);
		else if (retry == 14)
		{
			int avg = 0;
			std::cout << "The average killcount to finish zulrah was: " << avg / 25000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				clueBox finished = zulrah(0, 0);
				avg += finished.return1;
				finishedSet.push(finished.return1);
			}
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The mean killcount to finish zulrah was: " << finishedSet.top() << '\n';
		}
		else if (retry == 15)
			dags(1, 0);
		else if (retry == 16)
		{
			int avgTotal = 0;
			std::priority_queue<int> finishedSet;
			std::priority_queue<int> finishedRex;
			std::priority_queue<int> finishedSup;
			std::priority_queue<int> finishedPrime;
			for (int i = 0; i < 25000; i++)
			{
				dagBox holder = dags(0, 0);
				int totalHolder = holder.rex1;
				if (totalHolder < holder.supreme1)
					totalHolder = holder.supreme1;
				if (totalHolder < holder.prime1)
					totalHolder = holder.prime1;
				totalHolder *= 3;
				avgTotal += totalHolder;
				finishedSet.push(totalHolder);
				finishedRex.push(holder.rex1);
				finishedSup.push(holder.supreme1);
				finishedPrime.push(holder.prime1);
			}
			std::cout << "The average total killcount to finish dag kings was: " << avgTotal / 25000 << '\n';
			std::cout << "The worst killcount to finish Rex was " << finishedRex.top() << '\n';
			std::cout << "The worst killcount to finish Supreme was " << finishedSup.top() << '\n';
			std::cout << "The worst killcount to finish Prime was " << finishedPrime.top() << '\n';
			for (int i = 0; i < 12500; i++)
			{
				finishedSet.pop();
				finishedRex.pop();
				finishedSup.pop();
				finishedPrime.pop();
			}
			std::cout << "The median killcount to finish dag kings was: " << finishedSet.top() << '\n';
			std::cout << "The median killcount to finish Rex was " << finishedRex.top() << '\n';
			std::cout << "The median killcount to finish Supreme was " << finishedSup.top() << '\n';
			std::cout << "The median killcount to finish Prime was " << finishedPrime.top() << '\n';
		}
		else if (retry == 17)
			corp(1, 0);
		else if (retry == 18)
		{
			int avg = 0;
			std::cout << "The average killcount to finish corp was: " << avg / 25000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				clueBox finished = corp(0, 0);
				avg += finished.return1;
				finishedSet.push(finished.return1);
			}
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish corp was: " << finishedSet.top() << '\n';
		}
		else if (retry == 19)
			vorkath(1, 0);
		else if (retry == 20)
		{
			int avg = 0;
			std::cout << "The average killcount to finish vorkath was: " << avg / 25000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				clueBox finished = vorkath(0, 0);
				avg += finished.return1;
				finishedSet.push(finished.return1);
			}
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The mean killcount to finish vorkath was: " << finishedSet.top() << '\n';
		}
		else if (retry == 21)
			beginnerClue(1);
		else if (retry == 22)
		{
			const int TRIALS = 100000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++) // sort as being populated
			{
				int finished = beginnerClue(0);
				avg += finished;
				finishedSet.push(finished);
			}
			std::cout << "The average clue count to finish beginner clues was: " << avg / TRIALS << '\n';
			std::cout << "The highest chestcount to finish beginner clues was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median chestcount to finish beginner clues was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The best chestcount to finish beginner clues was: " << finishedSet.top() << '\n';
		}
		else if (retry == 23)
			easyClue(1);
		else if (retry == 24)
		{
			long long avg = 0;
			std::priority_queue<int> finishedSet;
			std::priority_queue<int> finishedMonk;
			std::priority_queue<int> finishedCape;
			for (int i = 0; i < 10000; i++) // sort as being populated
			{
				clueBox finished = easyClue(0);
				avg += finished.return1;
				finishedSet.push(finished.return1);
				finishedMonk.push(finished.return2);
				finishedCape.push(finished.return3);
			}
			std::cout << "The average clue count to finish easy clues was: " << avg / 10000 << '\n';
			std::cout << "The worst cluecount finish was " << finishedSet.top() << '\n';
			std::cout << "The most monk piece rolls was " << finishedMonk.top() << '\n';
			std::cout << "The most cape rolls was " << finishedCape.top() << '\n';
			for (int i = 0; i < 5000; i++)
			{
				finishedSet.pop();
				finishedMonk.pop();
				finishedCape.pop();
			}
			std::cout << "The median chestcount to finish easy clues was: " << finishedSet.top() << '\n';
			std::cout << "The median monk piece rolls was " << finishedMonk.top() << '\n';
			std::cout << "The median cape rolls was " << finishedCape.top() << '\n';
			for (int i = 0; i < 4999; i++)
			{
				finishedSet.pop();
				finishedMonk.pop();
				finishedCape.pop();
			}
			std::cout << "The lowest chestcount to finish easy clues was: " << finishedSet.top() << '\n';
			std::cout << "The lowest monk piece rolls was " << finishedMonk.top() << '\n';
			std::cout << "The lowest cape rolls was " << finishedCape.top() << '\n';
		}
		else if (retry == 25)
			mediumClue(1);
		else if (retry == 26)
		{
			long long avg = 0;
			std::priority_queue<int> finishedSet;
			std::priority_queue<int> finishedRangers;
			std::priority_queue<int> finishedMasters;
			for (int i = 0; i < 100000; i++) // sort as being populated
			{
				clueBox finished = mediumClue(0);
				avg += finished.return1;
				finishedSet.push(finished.return1);
				finishedRangers.push(finished.return2);
				finishedMasters.push(finished.return3);
			}
			double variance = 0;
			std::cout << "The average clue count to finish medium clues was: " << avg / 100000 << '\n';
			std::cout << "The worst finish was " << finishedSet.top() << '\n';
			std::cout << "The most rangers obtained was " << finishedRangers.top() << '\n';
			std::cout << "The most masters obtained was " << finishedMasters.top() << '\n';
			for (int i = 0; i < 50000; i++)
			{
				variance += pow((finishedSet.top() - (avg / 100000)), 2);
				finishedSet.pop();
				finishedRangers.pop();
				finishedMasters.pop();
			}
			std::cout << "The median chestcount to finish medium clues was: " << finishedSet.top() << '\n';
			std::cout << "The median rangers obtained was " << finishedRangers.top() << '\n';
			std::cout << "The median masters obtained was " << finishedMasters.top() << '\n';
			for (int i = 0; i < 49999; i++)
			{
				variance += pow((finishedSet.top() - (avg / 100000)), 2);
				finishedSet.pop();
				finishedRangers.pop();
				finishedMasters.pop();
			}
			variance = variance / 99999;
			double standardDeviation = sqrt(variance);
			std::cout << "The best chestcount to finish medium clues was: " << finishedSet.top() << '\n';
			std::cout << "The lowest rangers obtained was " << finishedRangers.top() << '\n';
			std::cout << "The lowest masters obtained was " << finishedMasters.top() << '\n';
			std::cout << "The sample variance for completing medium clues is: " << variance << '\n';
			std::cout << "The sample standard deviation for completing medium clues is: " << standardDeviation << '\n';
			std::cout << "A 99% confidence interval for the average medium clue finish is: (" << (avg / 99999) - 2.576 * (standardDeviation / sqrt(99999)) << "," << (avg / 99999) + 2.576 * (standardDeviation / sqrt(99999)) << ")\n";
		}
		else if (retry == 27)
			eliteClue(1);
		else if (retry == 28)
		{
			long long avg = 0;
			std::priority_queue<int> finishedSet;
			std::priority_queue<int> finishedMimics;
			std::priority_queue<int> finished3A;
			for (int i = 0; i < 25000; i++) // sort as being populated
			{
				clueBox counters = eliteClue(0);
				avg += counters.return1;
				finishedSet.push(counters.return1);
				finishedMimics.push(counters.return3);
				finished3A.push(counters.return2);
			}
			std::cout << "The average clue count to finish elite clues was: " << avg / 25000 << '\n';
			std::cout << "The worst completion was " << finishedSet.top();
			std::cout << "The most mimics was " << finishedMimics.top();
			std::cout << "The most 3rd age rolls was " << finished3A.top();
			for (int i = 0; i < 12500; i++)
			{
				finishedSet.pop();
				finishedMimics.pop();
				finished3A.pop();
			}
			std::cout << "The median chestcount to finish elite clues was: " << finishedSet.top() << '\n';
			std::cout << "The median mimics was " << finishedMimics.top();
			std::cout << "The median 3rd age rolls was " << finished3A.top();
			for (int i = 0; i < 12499; i++)
			{
				finishedSet.pop();
				finishedMimics.pop();
				finished3A.pop();
			}
			std::cout << "The best chestcount to finish elite clues was: " << finishedSet.top() << '\n';
			std::cout << "The lowest mimics was " << finishedMimics.top();
			std::cout << "The lowest 3rd age rolls was " << finished3A.top();
		}
		else if (retry == 29)
			masterClue(1, 0);
		else if (retry == 30)
		{
			long long avg = 0;
			const int TRIALS = 5000;
			std::priority_queue<int> finishedSet;
			std::priority_queue<int> finishedMimics;
			std::priority_queue<int> finished3A;
			for (int i = 0; i < TRIALS; i++) // sort as being populated
			{
				clueBox counters = masterClue(0,0);
				avg += counters.return1;
				finishedSet.push(counters.return1);
				finishedMimics.push(counters.return2);
				finished3A.push(counters.return3);
			}
			std::cout << "The average clue count to finish master clues was: " << avg / TRIALS << '\n';
			std::cout << "The worst completion was " << finishedSet.top();
			std::cout << "The most mimics was " << finishedMimics.top();
			std::cout << "The most 3rd age rolls was " << finished3A.top();
			for (int i = 0; i < TRIALS / 2; i++)
			{
				finishedSet.pop();
				finishedMimics.pop();
				finished3A.pop();
			}
			std::cout << "The median chestcount to finish master clues was: " << finishedSet.top() << '\n';
			std::cout << "The median mimics was " << finishedMimics.top() << '\n';
			std::cout << "The median 3rd age rolls was " << finished3A.top() << '\n';
			for (int i = 0; i < TRIALS / 2 -1; i++)
			{
				finishedSet.pop();
				finishedMimics.pop();
				finished3A.pop();
			}
			std::cout << "The best chestcount to finish master clues was: " << finishedSet.top() << '\n';
			std::cout << "The lowest mimics was " << finishedMimics.top() << '\n';
			std::cout << "The lowest 3rd age rolls was " << finished3A.top() << '\n';
		}
		else if (retry == 31)
			fishingTrawler(1);
		else if (retry == 32)
		{
			int avg = 0;
			for (int i = 0; i < 5000; i++)
				avg += fishingTrawler(0);
			std::cout << "The average game count to finish fishing trawler was: " << avg / 5000 << '\n';
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 5000; i++) // sort as being populated
			{
				int finished = fishingTrawler(0);
				finishedSet.push(finished);
			}
			for (int i = 0; i < 2500; i++)
				finishedSet.pop();
			std::cout << "The mean game count to finish fishing trawler was: " << finishedSet.top() << '\n';
		}
		else if (retry == 33)
			efficientThirdAge(1);
		else if (retry == 34)
		{
			long long hardAvg = 0, eliteAvg = 0, masterAvg = 0;
			std::priority_queue<int> finishedHardSet;
			std::priority_queue<int> finishedEliteSet;
			std::priority_queue<int> finishedMasterSet;
			std::priority_queue<thirdAgeBox> finishedClueSet;

			for (int i = 0; i < 10000; i++)
			{
				thirdAgeBox finish = efficientThirdAge(0);
				finish.time = (finish.hardClues * 6 + finish.eliteClues * 10 + finish.masterClues * 15) / 60;
				hardAvg += finish.hardClues;
				eliteAvg += finish.eliteClues;
				masterAvg += finish.masterClues;
				finishedHardSet.push(finish.hardClues);
				finishedEliteSet.push(finish.eliteClues);
				finishedMasterSet.push(finish.masterClues);
				finishedClueSet.push(finish);
				if (i % 1000 == 0)
					std::cout << i << " simulations completed.\n";
			}

			std::cout << "The average casket count to finish hard+ collection log was:\n";
			std::cout << "Hard Clues: " << hardAvg / 10000 << '\n';
			std::cout << "Elite Clues: " << eliteAvg / 10000 << '\n';
			std::cout << "Master Clues: " << masterAvg / 10000 << '\n';

			std::cout << "The worst hard casket count is: " << finishedHardSet.top() << '\n';
			std::cout << "The worst elite casket count is: " << finishedEliteSet.top() << '\n';
			std::cout << "The worst master casket count is: " << finishedMasterSet.top() << '\n';
			std::cout << "The worst time to complete the clues is: " << finishedClueSet.top().time << ", with a breakdown of, Hard:" << finishedClueSet.top().hardClues
				<< ", Elite:" << finishedClueSet.top().eliteClues << ", Master:" << finishedClueSet.top().masterClues << '\n';
			for (int i = 0; i < 5000; i++)
			{
				finishedHardSet.pop();
				finishedEliteSet.pop();
				finishedMasterSet.pop();
				finishedClueSet.pop();
			}
			std::cout << "The median hard casket count is: " << finishedHardSet.top() << '\n';
			std::cout << "The median elite casket count is: " << finishedEliteSet.top() << '\n';
			std::cout << "The median master casket count is: " << finishedMasterSet.top() << '\n';
			std::cout << "The median time to complete the clues is: " << finishedClueSet.top().time << ", with a breakdown of, Hard:" << finishedClueSet.top().hardClues
				<< ", Elite:" << finishedClueSet.top().eliteClues << ", Master:" << finishedClueSet.top().masterClues << '\n';
			for (int i = 0; i < 4999; i++)
			{
				finishedHardSet.pop();
				finishedEliteSet.pop();
				finishedMasterSet.pop();
				finishedClueSet.pop();
			}
			std::cout << "The best hard casket count is: " << finishedHardSet.top() << '\n';
			std::cout << "The best elite casket count is: " << finishedEliteSet.top() << '\n';
			std::cout << "The best master casket count is: " << finishedMasterSet.top() << '\n';
			std::cout << "The best time to complete the clues is: " << finishedClueSet.top().time << ", with a breakdown of, Hard:" << finishedClueSet.top().hardClues
				<< ", Elite:" << finishedClueSet.top().eliteClues << ", Master:" << finishedClueSet.top().masterClues << '\n';
		}
		else if (retry == 35)
			alchemicalHydra(1, 0);
		else if (retry == 36)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedHydra;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = alchemicalHydra(0, 0);
				avg += holder.return1;
				finishedHydra.push(holder.return1);
			}
			std::cout << "The average killcount to complete hydra is " << avg / TRIALS << '\n';
			std::cout << "The worst game count to finish Alchemical Hydra was: " << finishedHydra.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedHydra.pop();
			std::cout << "The median game count to finish Alchemical Hydra was: " << finishedHydra.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedHydra.pop();
			std::cout << "The best game count to finish Alchemical Hydra was: " << finishedHydra.top() << '\n';
		}
		else if (retry == 37)
			callisto(1, 0);
		else if (retry == 38)
		{
			int avg = 0;
			std::priority_queue<int> finishedCallisto;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = callisto(0, 0);
				avg += holder.return1;
				finishedCallisto.push(holder.return1);
			}
			std::cout << "The average killcount to complete Callisto is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedCallisto.pop();
			std::cout << "The median killcount to finish Callisto was: " << finishedCallisto.top() << '\n';
		}
		else if (retry == 39)
			cerberus(1, 0);
		else if (retry == 40)
		{
			const int TRIALS = 1000;
			int avg = 0;
			std::priority_queue<int> finishedCerberus;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = cerberus(0, 0);
				avg += holder.return1;
				finishedCerberus.push(holder.return1);
			}
			std::cout << "The average killcount to complete Cerberus is " << avg / TRIALS << '\n';
			std::cout << "The best killcount to finish Cerberus was: " << finishedCerberus.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedCerberus.pop();
			std::cout << "The median killcount to finish Cerberus was: " << finishedCerberus.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedCerberus.pop();
			std::cout << "The worst killcount to finish Cerberus was: " << finishedCerberus.top() << '\n';
		}
		else if (retry == 41)
			gauntlet(1, 0);
		else if (retry == 42)
		{
			int avg = 0;
			std::priority_queue<int> finishedGauntlet;
			for (int i = 0; i < 50000; i++)
			{
				clueBox holder = gauntlet(0, 0);
				avg += holder.return1;
				finishedGauntlet.push(holder.return1);
			}
			std::cout << "The average killcount to complete corruped gauntlet is " << avg / 50000 << '\n';
			for (int i = 0; i < 25000; i++)
				finishedGauntlet.pop();
			std::cout << "The median killcount to finish corrupted gauntlet was: " << finishedGauntlet.top() << '\n';
		}
		else if (retry == 43)
			chaosFanatic(1, 0);
		else if (retry == 44)
		{
			int avg = 0, holder = 0;
			std::priority_queue<int> finishedFanatic;
			for (int i = 0; i < 25000; i++)
			{
				holder = chaosFanatic(0, 0);
				avg += holder;
				int finished = holder;
				finishedFanatic.push(finished);
			}
			std::cout << "The average killcount to complete chaos fanatic is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedFanatic.pop();
			std::cout << "The median killcount to finish chaos fanatic was: " << finishedFanatic.top() << '\n';
		}
		else if (retry == 45)
			zily(1, 0);
		else if (retry == 46)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = zily(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Zily is " << avg / TRIALS << '\n';
			std::cout << "The worst killcount to finish Zilyana was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Zilyana was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The best killcount to finish Zilyana was: " << finishedSet.top() << '\n';
		}
		else if (retry == 47)
			jad(1);
		else if (retry == 48)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = jad(0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Jad is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Jad was: " << finishedSet.top() << '\n';
		}
		else if (retry == 49)
			graardor(1, 0);
		else if (retry == 50)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = graardor(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Graardor is " << avg / TRIALS << '\n';
			std::cout << "The worst killcount to finish Graardor was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Graardor was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The lowest killcount to finish Graardor was: " << finishedSet.top() << '\n';
		}
		else if (retry == 51)
			mole(1);
		else if (retry == 52)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = mole(0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete mole is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish mole was: " << finishedSet.top() << '\n';
		}
		else if (retry == 53)
			grotGuardians(1, 0);
		else if (retry == 54)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = grotGuardians(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete grotesque guardians is " << avg / TRIALS << '\n';
			std::cout << "The worst killcount to finish grotesque guardians was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish grotesque guardians was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The best killcount to finish grotesque guardians was: " << finishedSet.top() << '\n';
		}
		else if (retry == 55)
			kalphiteQueen(1, 0);
		else if (retry == 56)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = kalphiteQueen(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Kalphite Queen is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Kalphite Queen was: " << finishedSet.top() << '\n';
		}
		else if (retry == 57)
			kbd(1, 0);
		else if (retry == 58)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = kbd(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete king black dragon is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish king black dragon was: " << finishedSet.top() << '\n';
		}
		else if (retry == 59)
			kraken(1, 0);
		else if (retry == 60)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = kraken(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete kraken is " << avg / TRIALS << '\n';
			std::cout << "The worst killcount to finish kraken was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish kraken was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The best killcount to finish kraken was: " << finishedSet.top() << '\n';
		}
		else if (retry == 61)
			kril(1, 0);
		else if (retry == 62)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = kril(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete kril is " << avg / TRIALS << '\n';
			std::cout << "The worst killcount to finish kril was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish kril was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The best killcount to finish kril was: " << finishedSet.top() << '\n';
		}
		else if (retry == 63)
			nightmare(1, 0);
		else if (retry == 64)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = nightmare(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete The Nightmare is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish The Nightmare was: " << finishedSet.top() << '\n';
		}
		else if (retry == 65)
			sarachnis(1, 0);
		else if (retry == 66)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = sarachnis(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Sarachnis is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Sarachnis was: " << finishedSet.top() << '\n';
		}
		else if (retry == 67)
			scorpia(1, 0);
		else if (retry == 68)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = scorpia(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Scorpia is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Scorpia was: " << finishedSet.top() << '\n';
		}
		else if (retry == 69)
			skotizo(1, 0);
		else if (retry == 70)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = skotizo(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Skotizo is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Skotizo was: " << finishedSet.top() << '\n';
		}
		else if (retry == 71)
			thermy(1, 0);
		else if (retry == 72)
		{
		const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++)
			{
				clueBox holder = thermy(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Thermy is " << avg / TRIALS << '\n';
			std::cout << "The worst killcount to finish Thermy was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Thermy was: " << finishedSet.top() << '\n';
			for (int i = 0; i < TRIALS / 2 - 1; i++)
				finishedSet.pop();
			std::cout << "The best killcount to finish Thermy was: " << finishedSet.top() << '\n';
		}
		else if (retry == 73)
			venenatis(1, 0);
		else if (retry == 74)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = venenatis(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Venenatis is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Venenatis was: " << finishedSet.top() << '\n';
		}
		else if (retry == 75)
			vetion(1, 0);
		else if (retry == 76)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = vetion(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Vetion is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Vetion was: " << finishedSet.top() << '\n';
		}
		else if (retry == 77)
			zalcano(1, 0);
		else if (retry == 78)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = zalcano(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Zalcano is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Zalcano was: " << finishedSet.top() << '\n';
		}
		else if (retry == 79)
			challengeXericSolo(1, 0);
		else if (retry == 80)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = challengeXericSolo(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Chambers of Xeric through challenge mode is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Chambers of Xeric challenge mode was: " << finishedSet.top() << '\n';
		}
		else if (retry == 81)
			theater(1, 0);
		else if (retry == 82)
		{
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < 25000; i++)
			{
				clueBox holder = theater(0, 0);
				avg += holder.return1;
				finishedSet.push(holder.return1);
			}
			std::cout << "The average killcount to complete Theater of Blood is " << avg / 25000 << '\n';
			for (int i = 0; i < 12500; i++)
				finishedSet.pop();
			std::cout << "The median killcount to finish Theater of Blood was: " << finishedSet.top() << '\n';
		}
		else if (retry == 83)
			chinchompa(1);
		else if (retry == 84)
			beaver(1);
		else if (retry == 85)
			squirrel(1);
		else if (retry == 86)
			heron(1);
		else if (retry == 87)
			rift(1);
		else if (retry == 88)
			golem(1);
		else if (retry == 89)
			rocky(1);
		else if (retry == 90)
			tangle(1);
		else if (retry == 91)
			chompy(1);
		else if (retry == 92)
			herbi(1);
		else if (retry == 93)
			penance(1);
		else if (retry == 94)
			petRun(1, 0);
		else if (retry == 95)
			petRun(0, 0);
		else if (retry == 96)
		{
			long double avgTime = 0, avgPetRate = 0;
			petBox holder;
			const int TRIALS = 25000;
			std::priority_queue<petBox> finishedSet;
			std::priority_queue<double> finishedBest;
			std::priority_queue<double> finishedWorst;
			std::priority_queue<double> finishedAvgPetRate;
			std::priority_queue<double> finishedGp;
			std::priority_queue<double> finishedFreeElites;
			std::priority_queue<double> preFinishedGp;
			for (int i = 0; i < TRIALS; i++)
			{
				holder = petRun(0, 1);
				avgTime += holder.time;
				avgPetRate += holder.petDropRate;
				petBox finished = holder;
				finishedSet.push(finished);
				finishedBest.push(finished.bestRate);
				finishedWorst.push(finished.worstRate);
				finishedAvgPetRate.push(finished.petDropRate);
				finishedGp.push(finished.finishedGp);
				finishedFreeElites.push(finished.finishedBonusElites);
				preFinishedGp.push(finished.finishedGpBeforeHound);
				if (i % 1000 == 0)
					std::cout << i << " simulations completed.\n";
			}
			long double variance = 0;
			avgTime = avgTime / TRIALS;
			std::cout << "The average hours to complete all pets is " << avgTime << '\n';
			std::cout << "The worst time to complete all pets was " << finishedSet.top().time << " hours to finish with a breakdown of " << finishedSet.top().bestRate << " luckiest pet and "
				<< finishedSet.top().worstRate << " worst pet and " << finishedSet.top().petDropRate << " average pet rate drop.\n"
				"This person made " << finishedSet.top().finishedGpBeforeHound << " but finished with " << finishedSet.top().finishedGp << " and they got " << finishedSet.top().finishedBonusElites
				<< " bonus elites while pet hutning.\n";
			std::cout << "The average pet drop rate for entire sample was " << avgPetRate / TRIALS << '\n';
			std::cout << "The highest worst pet drop rate anyone got was " << finishedWorst.top() << "\n";
			std::cout << "The highest best pet drop rate anyone got was " << finishedBest.top() << '\n';
			std::cout << "The highest average pet drop rate anyone got was " << finishedAvgPetRate.top() << '\n';
			std::cout << "The most gp anyone finished all pets with was " << finishedGp.top() << '\n';
			std::cout << "The most gp anyone finsihed all but bloodhound with was " << preFinishedGp.top() << '\n';
			std::cout << "The most bonus elite clues anyone got was " << finishedFreeElites.top() << '\n';

			for (int i = 0; i < TRIALS/2; i++)
			{
				variance += pow(finishedSet.top().time - avgTime, 2);
				finishedSet.pop();
				finishedBest.pop();
				finishedWorst.pop();
				finishedAvgPetRate.pop();
				finishedGp.pop();
				preFinishedGp.pop();
				finishedFreeElites.pop();
			}
			std::cout << "The median hours to complete all pets is " << finishedSet.top().time << '\n';
			std::cout << "Out of every pet completion, in the simulations the median worst pet rate was " << finishedWorst.top() << '\n';
			std::cout << "Out of every pet completion, in the simulations the median best pet rate was " << finishedBest.top() << '\n';
			std::cout << "The median average pet drop rate was " << finishedAvgPetRate.top() << '\n';
			std::cout << "The median gp anyone finished all pets with was " << finishedGp.top() << '\n';
			std::cout << "The median gp anyone finsihed all but bloodhound with was " << preFinishedGp.top() << '\n';
			std::cout << "The median bonus elite clues anyone got was " << finishedFreeElites.top() << '\n';
			for (int i = 0; i < TRIALS/2 - 1; i++)
			{
				variance += pow(finishedSet.top().time - avgTime, 2);
				finishedSet.pop();
				finishedBest.pop();
				finishedWorst.pop();
				finishedAvgPetRate.pop();
				finishedGp.pop();
				preFinishedGp.pop();
				finishedFreeElites.pop();
			}
			variance = variance / TRIALS;
			double standardDeviation = sqrt(variance);
			std::cout << "The best time to complete all pets was " << finishedSet.top().time << " hours.\n";
			std::cout << "The sample variance for these simulations was " << variance << " and the standard deviation was " << standardDeviation << ".\n";
			std::cout << "The lowest worst pet drop rate anyone got was " << finishedWorst.top() << '\n';
			std::cout << "The lowest best pet drop rate anyone got was " << finishedBest.top() << '\n';
			std::cout << "The lowest average pet drop rate was " << finishedAvgPetRate.top() << '\n';
			std::cout << "The least gp anyone finished all pets with was " << finishedGp.top() << '\n';
			std::cout << "The least gp anyone finsihed all but bloodhound with was " << preFinishedGp.top() << '\n';
			std::cout << "The least bonus elite clues anyone got was " << finishedFreeElites.top() << '\n';
		}
		else if (retry == 97)
			efficientThirdAgeTwo(1);
		else if (retry == 98)
		{
			long long hardAvg = 0, eliteAvg = 0, masterAvg = 0;
			const int TRIALS = 25000;
			std::priority_queue<int> finishedHardSet;
			std::priority_queue<int> finishedEliteSet;
			std::priority_queue<int> finishedMasterSet;
			std::priority_queue<thirdAgeBox> finishedClueSet;
			for (int i = 0; i < TRIALS; i++)
			{
				thirdAgeBox finish = efficientThirdAgeTwo(0);
				finish.time = finish.time / 60;
				hardAvg += finish.hardClues;
				eliteAvg += finish.eliteClues;
				masterAvg += finish.masterClues;
				finishedHardSet.push(finish.hardClues);
				finishedEliteSet.push(finish.eliteClues);
				finishedMasterSet.push(finish.masterClues);
				finishedClueSet.push(finish);
				if (i % 1000 == 0)
					std::cout << i << " simulations completed.\n";
			}

			std::cout << "The average casket count to finish hard+ collection log was:\n";
			std::cout << "Hard Clues: " << hardAvg / TRIALS << '\n';
			std::cout << "Elite Clues: " << eliteAvg / TRIALS << '\n';
			std::cout << "Master Clues: " << masterAvg / TRIALS << '\n';

			std::cout << "The worst hard casket count is: " << finishedHardSet.top() << '\n';
			std::cout << "The worst elite casket count is: " << finishedEliteSet.top() << '\n';
			std::cout << "The worst master casket count is: " << finishedMasterSet.top() << '\n';
			std::cout << "The worst time to complete the clues is: " << finishedClueSet.top().time << ", with a breakdown of, Hard:" << finishedClueSet.top().hardClues
				<< ", Elite:" << finishedClueSet.top().eliteClues << ", Master:" << finishedClueSet.top().masterClues << '\n';
			for (int i = 0; i < TRIALS/2; i++)
			{
				finishedHardSet.pop();
				finishedEliteSet.pop();
				finishedMasterSet.pop();
				finishedClueSet.pop();
			}
			std::cout << "The median hard casket count is: " << finishedHardSet.top() << '\n';
			std::cout << "The median elite casket count is: " << finishedEliteSet.top() << '\n';
			std::cout << "The median master casket count is: " << finishedMasterSet.top() << '\n';
			std::cout << "The median time to complete the clues is: " << finishedClueSet.top().time << ", with a breakdown of, Hard:" << finishedClueSet.top().hardClues
				<< ", Elite:" << finishedClueSet.top().eliteClues << ", Master:" << finishedClueSet.top().masterClues << '\n';
			for (int i = 0; i < TRIALS/2 - 1; i++)
			{
				finishedHardSet.pop();
				finishedEliteSet.pop();
				finishedMasterSet.pop();
				finishedClueSet.pop();
			}
			std::cout << "The best hard casket count is: " << finishedHardSet.top() << '\n';
			std::cout << "The best elite casket count is: " << finishedEliteSet.top() << '\n';
			std::cout << "The best master casket count is: " << finishedMasterSet.top() << '\n';
			std::cout << "The best time to complete the clues is: " << finishedClueSet.top().time << ", with a breakdown of, Hard:" << finishedClueSet.top().hardClues
				<< ", Elite:" << finishedClueSet.top().eliteClues << ", Master:" << finishedClueSet.top().masterClues << '\n';
		}
		else if (retry == 99)
			hardCluesBloodhound(1);
			//auto dice_rand = std::bind(std::uniform_int_distribution<int>(1, 6), std::mt19937(seed));
			std::cout << "\n\nExit [0]\nBarrows Finish[1]\nAvg Barrows Finish[2]\nHard Clues Finish[3]\nAvg Hard Clue Finish[4]\nArmadyl Finish[5]\nAvg Armadyl Finish[6]"
			"\nWintertodt Finish[7]\nAvg Wintertodt Finish[8]\nAbby Sire Finish[9]\nAvg Abby Sire Finish[10]\nBryophyta Finish[11]\nAvg Bryophyta Finish[12]\n"
			"Finish Zulrah[13]\nAvg Finish Zulrah[14]\nDag Kings Finish[15]\nAvg Dag Kings Finish[16]\nCorp Finish[17]\nAvg Corp Finish[18]\nFinish Vorkath[19]\nAvg Vorkath Finish[20]\n"
			"Finish Beginner Clues[21]\nAvg Finish Beginner Clues[22]\nFinish Easy Clues[23]\nAvg Finish Easy Clues[24]\nFinish Med Clues[25]\nAvg Med Clues Finish[26]\nFinish Elite Clues[27]"
			"\nAvg Finish Elite Clues[28]\nFinish Master Clues[29]\nAvg Finish Master Clues[30]\nFinish fishing trawler[31]\nAvg Fishing Trawler Finish[32]\nEfficient 3rd Age Finish[33]\n"
			"Avg Efficient 3rd Age Finish[34]\nFinish Alchemical Hydra[35]\nAvg Finish Alchemical Hydra[36]\nFinish Callisto[37]\nAvg Finish Callisto[38]\nFinish Cerberus[39]\nAvg "
			"Finish Cerberus[40]\nFinish Gauntlet[41]\nAvg Gauntlet Finish[42]\nFinish Chaos Fanatic[43]\nAvg Chaos Fanatic Finish[44]\nFinish Zily[45]\nAvg Zily Finish[46]\nFinish Jad[47]\n"
			"Avg Jad Finish[48]\nFinish Graardor[49]\nAvg Graardor Finish[50]\nFinish Giant Mole[51]\nAvg Giant Mole Finish[52]\nFinish Grotesque Guardians[53]\nAvg Grotesque Gaurdian Finish[54]\n"
			"Finish Kalphite Queen[55]\nAvg Kalphite Queen Finish[56]\nFinish King Black Dragon[57]\nAvg King Black Dragon Finish[58]\nFinish Kraken[59]\nAvg Kraken Finish[60]\nFinish Kril[61]"
			"\nAvg Kril Finish[62]\nFinish The Nightmare[63]\nAvg Nightmare Finish[64]\nFinish Sarachnis[65]\nAvg Sarachnis Finish[66]\nFinish Scorpia[67]\nAvg Scorpia Finish[68]\nFinish Skotizo[69]\n"
			"Avg Skotizo Finish[70]\nFinish Thermy[71]\nAvg Thermy Finish[72]\nFinish Venenatis[73]\nAvg Venenatis Finish[74]\nFinish Vetion[75]\nAvg Vetion Finish[76]\nZalcano Finish[77]\nAvg Zalcano"
			" Finish[78]\nFinish Solo Challenge Cox[79]\nAvg Solo Challenge Cox Finish[80]\nFinish Theater of Blood[81]\nAvg Theater of Blood Finish[82]\nFinish Chinchompa Pet[83]\nFinish Beaver[84]\n"
			"Finish Giant Squirrel[85]\nFinish Heron[86]\nFinish Rift Guardian[87]\nFinish Rock Golem[88]\nFinish Rocky[89]\nFinish Tangleroot[90]\nFinish Chompy Chick[91]\nFinish Herbi[92]\n"
			"Finish Penance pet[93]\nComplete all Pets[94]\nComplete all Pets Quick[95]\naAvg all Pets Completion[96]\nFinish 3rd Age No Dragon Imps[97]\nAvg 3rd Age Finish No Dragon Imps[98]\n";
		std::cin >> retry;
	}

	return 0;
}


int barrows(int option)
{
	int AhrimHood = 0, AhrimTop = 0, AhrimBottom = 0, AhrimStaff = 0,
		KarilCoif = 0, KarilTop = 0, KarilBottom = 0, KarilBow = 0,
		DharokHelm = 0, DharokPlate = 0, DharokLegs = 0, DharokAxe = 0,
		ToragHelm = 0, ToragPlate = 0, ToragLegs = 0, ToragHammers = 0,
		VeracHelm = 0, VeracChest = 0, VeracSkirt = 0, VeracFlail = 0,
		GuthanHelm = 0, GuthanChest = 0, GuthanSkirt = 0, GuthanSpear = 0,
		eliteClue = 0;
	int killcount = 0;

	while (AhrimHood == 0 || AhrimTop == 0 || AhrimBottom == 0 || AhrimStaff == 0 ||
		KarilCoif == 0 || KarilTop == 0 || KarilBottom == 0 || KarilBow == 0 ||
		DharokHelm == 0 || DharokPlate == 0 || DharokLegs == 0 || DharokAxe == 0 ||
		ToragHelm == 0 || ToragPlate == 0 || ToragLegs == 0 || ToragHammers == 0 ||
		VeracHelm == 0 || VeracChest == 0 || VeracSkirt == 0 || VeracFlail == 0 ||
		GuthanHelm == 0 || GuthanChest == 0 || GuthanSkirt == 0 || GuthanSpear == 0)
	{
		bool eliteTrue = false;
		int memory1 = 0, memory2 = 0, memory3 = 0, memory4 = 0, memory5 = 0, memory6 = 0;// can't get same item twice, need to remember item that i get
		for (int roll = 0; roll < 7; roll++)
		{
			int eliteRoll = rand() % 200 + 1;
			if (eliteRoll == 1 && eliteTrue == false)
			{
				eliteClue++;
				eliteTrue = true;
			}
			int barrowRoll = rand() % 102 + 1; //Roll for barrows table, will be 6 of these
			if (barrowRoll == 1) // enter barrows table for an item
			{
				int tableRoll = rand() % 24 + 1; //24 Items on table, decide which 1
				while (tableRoll == memory1 || tableRoll == memory2 || tableRoll == memory3 || tableRoll == memory4 || tableRoll == memory5 || tableRoll == memory6)
					tableRoll = rand() % 24 + 1;
				if (roll == 1)
					memory1 = roll;
				else if (roll == 2)
					memory2 = roll;
				else if (roll == 3)
					memory3 = roll;
				else if (roll == 4)
					memory4 = roll;
				else if (roll == 5)
					memory5 = roll;
				else if (roll == 6)
					memory6 = roll;
				if (tableRoll == 1)
					AhrimHood++;
				else if (tableRoll == 2)
					AhrimTop++;
				else if (tableRoll == 3)
					AhrimBottom++;
				else if (tableRoll == 4)
					AhrimStaff++;
				else if (tableRoll == 5)
					KarilCoif++;
				else if (tableRoll == 6)
					KarilTop++;
				else if (tableRoll == 7)
					KarilBottom++;
				else if (tableRoll == 8)
					KarilBow++;
				else if (tableRoll == 9)
					DharokHelm++;
				else if (tableRoll == 10)
					DharokPlate++;
				else if (tableRoll == 11)
					DharokLegs++;
				else if (tableRoll == 12)
					DharokAxe++;
				else if (tableRoll == 13)
					ToragHelm++;
				else if (tableRoll == 14)
					ToragPlate++;
				else if (tableRoll == 15)
					ToragLegs++;
				else if (tableRoll == 16)
					ToragHammers++;
				else if (tableRoll == 17)
					VeracHelm++;
				else if (tableRoll == 18)
					VeracChest++;
				else if (tableRoll == 19)
					VeracSkirt++;
				else if (tableRoll == 20)
					VeracFlail++;
				else if (tableRoll == 21)
					GuthanHelm++;
				else if (tableRoll == 22)
					GuthanChest++;
				else if (tableRoll == 23)
					GuthanSkirt++;
				else if (tableRoll == 24)
					GuthanSpear++;
			}
		}
		killcount++;
	}
	if (option == 1)
	{
		std::cout << "Ahrim's Hood: " << AhrimHood << '\n';
		std::cout << "Ahrim's Top: " << AhrimTop << '\n';
		std::cout << "Ahrim's Bottoms: " << AhrimBottom << '\n';
		std::cout << "Ahrim's Staff: " << AhrimStaff << '\n';
		std::cout << "Karil's Coif: " << KarilCoif << '\n';
		std::cout << "Karils Top: " << KarilTop << '\n';
		std::cout << "Karil's Bottoms: " << KarilBottom << '\n';
		std::cout << "Karil's Bow: " << KarilBow << '\n';
		std::cout << "Dharok's Helm: " << DharokHelm << '\n';
		std::cout << "Dharok's Plate: " << DharokPlate << '\n';
		std::cout << "Dharok's Legs: " << DharokLegs << '\n';
		std::cout << "Dharok's Axe: " << DharokAxe << '\n';
		std::cout << "Torag's Helm: " << ToragHelm << '\n';
		std::cout << "Torag's Plate: " << ToragPlate << '\n';
		std::cout << "Torag's Legs: " << ToragLegs << '\n';
		std::cout << "Torag's Hammers: " << ToragHammers << '\n';
		std::cout << "Verac's Helm: " << VeracHelm << '\n';
		std::cout << "Verac's Brassy: " << VeracChest << '\n';
		std::cout << "Verac's Skirt: " << VeracSkirt << '\n';
		std::cout << "Verac's Flail: " << VeracFlail << '\n';
		std::cout << "Guthan's Helm: " << GuthanHelm << '\n';
		std::cout << "Guthan's Plate: " << GuthanChest << '\n';
		std::cout << "Guthan's Skirt: " << GuthanSkirt << '\n';
		std::cout << "Guthan's Spear: " << GuthanSpear << '\n';
		std::cout << "Elite Clues: " << eliteClue << '\n';
		std::cout << "Killcount: " << killcount << '\n';
	}

	return killcount;
}

clueBox hardClues(int option)
{
	// https://docs.google.com/spreadsheets/d/16pVNHdZyynmxIbM9mynRDYT0LQsWxq-vbDs4_7DpnGM/edit#gid=1062333316
	//random 4-6 rolls
	// 1/15 for master
	// 1/13 for rare
	// 1/1625 for mega rare(1/125 on rare table)

	std::ifstream readFile;
	itemBox* itemTracker;
	itemTracker = new itemBox[161];
	int i = 0;
	readFile.open("hardClueItems.txt");
	if (!readFile.is_open())
		std::cout << "Error opening file.\n";
	else
	{
		while (!readFile.eof())
		{
			readFile >> itemTracker[i].itemName;
			itemTracker[i].amount = 0;
			i++;
		}
	}

	int  counter = 0, masterCount = 0, gildedCount = 0, thirdAgeRolls = 0;
	bool finishCheck = false;

	while (finishCheck == false)
	{
		int hardRolls = rand() % 3 + 4;
		for (int i = 0; i < hardRolls; i++)
		{
			int initialRoll = rand() % 13;
			if (initialRoll == 1)
			{
				int rareRoll = rand() % 125 + 1;
				if (rareRoll < 123) // mega rare table
					itemTracker[rareRoll + 27].amount++;
				else if (rareRoll == 123)
				{
					int megaRareRoll = rand() % 10 + 1;
					if (megaRareRoll < 6)
					{
						int gildRoll = rand() % 11 + 4; // gilded pieces are position 4-14
						itemTracker[gildRoll].amount++;
						gildedCount++;
					}
					else if (megaRareRoll == 6)
					{
						int thirdAgeRoll = rand() % 13 + 15; // third age pieces are position 15-27
						itemTracker[thirdAgeRoll].amount++;
						thirdAgeRolls++;
					}
					else
					{
						itemTracker[megaRareRoll - 7].amount++; // potions are position 0-3
					}
				}
				else if (rareRoll == 124)
				{
					int shieldRoll = rand() % 6 + 150;
					itemTracker[shieldRoll].amount++; // shields are position 150-155
				}
				else if (rareRoll == 125)
				{
					int plateRoll = rand() % 5 + 156;
					itemTracker[plateRoll].amount++; // heraldic plate positions 156-160
				}
			}
		}
		int master = rand() % 15 + 1;
		if (master == 1)
			masterCount++;
		counter++;
		finishCheck = true;
		for (int a = 4; a < 15; a++) // set a = 0 for every item, set a = 28 to skip mega rare table
		{
			if (itemTracker[a].amount == 0)
				finishCheck = false;
		}
	}

	if (option == 1)
	{
		std::cout << "Total hard clues completed: " << counter << '\n';
		std::cout << "Total masters: " << masterCount << '\n';
		for (int i = 4; i < 15; i++)
			std::cout << itemTracker[i].itemName << " : " << itemTracker[i].amount << '\n';
	}
	delete[] itemTracker;
	clueBox returnCounters;
	returnCounters.return1 = counter;
	returnCounters.return2 = thirdAgeRolls;
	returnCounters.return3 = gildedCount;
	readFile.close();
	return returnCounters;
}

clueBox armadyl(int option, bool petOnly)
{
	int armadylHelm = 0, armadylChest = 0, armadylSkirt = 0, armadylHilt = 0, armadylPet = 0, shard1 = 0, shard2 = 0, shard3 = 0, counter = 0, clue = 0;
	long long int gp = 0;
	if (petOnly == 0)
	{
		while (armadylHelm == 0 || armadylChest == 0 || armadylSkirt == 0 || armadylHilt == 0 || shard1 == 0 || shard2 == 0 || shard3 == 0 || armadylPet == 0)
		{
			for (int i = 0; i < 4; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 == 1)
						armadylHelm++;
					else if (minionRoll2 == 2)
						armadylChest++;
					else if (minionRoll2 == 3)
						armadylSkirt++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}
			int drop = rand() % 127 + 1;
			int pet = rand() % 100 + 1; //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
			if (pet == 1)
			{
				int petRoll = rand() % 50 + 1;
				if (petRoll == 1)
					armadylPet++;
			}
			if (drop == 1)
			{
				int rare = rand() % 3 + 1;
				if (rare == 1)
					armadylHelm++;
				else if (rare == 2)
					armadylChest++;
				else if (rare == 3)
					armadylSkirt++;
			}
			else if (drop == 2)
			{
				int hilt = rand() % 4;
				if (hilt == 0)
					armadylHilt++;
			}
			else if (drop == 3)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			counter++;
			int clueRoll = rand() % 250;
			if (clueRoll == 10)
				clue++;
		}
		gp += armadylHelm * ARMADYLHELM;
		gp += armadylChest * ARMADYLCHEST;
		gp += armadylSkirt * ARMADYLSKIRT;
		gp += shard1 * GODSHARD1;
		gp += shard2 * GODSHARD2;
		gp += shard3 * GODSHARD3;
		gp += counter * ARMADYLSTANDARD;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total armadyl helms: " << armadylHelm << '\n';
			std::cout << "Total armadyl chestplates: " << armadylChest << '\n';
			std::cout << "Total armadyl plateskirts: " << armadylSkirt << '\n';
			std::cout << "Total armadyl hilts: " << armadylHilt << '\n';
			std::cout << "Total armadyl pets: " << armadylPet << '\n';
			std::cout << "Total gp: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (armadylPet == 0)
		{
			for (int i = 0; i < 4; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 == 1)
						armadylHelm++;
					else if (minionRoll2 == 2)
						armadylChest++;
					else if (minionRoll2 == 3)
						armadylSkirt++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}
			int drop = rand() % 127 + 1;
			int pet = rand() % 100 + 1; //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
			if (pet == 1)
			{
				int petRoll = rand() % 50 + 1;
				if (petRoll == 1)
					armadylPet++;
			}
			if (drop == 1)
			{
				int rare = rand() % 3 + 1;
				if (rare == 1)
					armadylHelm++;
				else if (rare == 2)
					armadylChest++;
				else if (rare == 3)
					armadylSkirt++;
			}
			else if (drop == 2)
			{
				int hilt = rand() % 4;
				if (hilt == 0)
					armadylHilt++;
			}
			else if (drop == 3)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			counter++;
			int clueRoll = rand() % 250;
			if (clueRoll == 10)
				clue++;
		}
		gp += armadylHelm * ARMADYLHELM;
		gp += armadylChest * ARMADYLCHEST;
		gp += armadylSkirt * ARMADYLSKIRT;
		gp += shard1 * GODSHARD1;
		gp += shard2 * GODSHARD2;
		gp += shard3 * GODSHARD3;
		gp += counter * ARMADYLSTANDARD;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total armadyl helms: " << armadylHelm << '\n';
			std::cout << "Total armadyl chestplates: " << armadylChest << '\n';
			std::cout << "Total armadyl plateskirts: " << armadylSkirt << '\n';
			std::cout << "Total armadyl hilts: " << armadylHilt << '\n';
			std::cout << "Total armadyl pets: " << armadylPet << '\n';
			std::cout << "Total gp: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox abyssalSire(int option, bool petOnly)
{
	int jar = 0, head = 0, whip = 0, bludgeon = 0, dagger = 0, pet = 0, counter = 0, clues = 0;
	long long int gp = 0;
	if (petOnly == 0)
	{
		while (jar == 0 || head == 0 || whip == 0 || bludgeon < 3 || dagger == 0 || pet == 0)
		{
			int roll = rand() % 100 + 1;
			if (roll == 1)
			{
				int rare = rand() % 128 + 1;
				if (rare < 14)
					jar++;
				else if (rare > 13 && rare < 24)
					head++;
				else if (rare > 23 && rare < 36)
					whip++;
				else if (rare > 35 && rare < 98)
					bludgeon++;
				else if (rare > 97 && rare < 124)
					dagger++;
				else if (rare > 123)
					pet++;
			}
			counter++;
			int clueRoll = rand() % 180;
			if (clueRoll == 1)
				clues++;
		}

		gp += whip * WHIP;
		gp += dagger * ABBYDAGGER;
		gp += (bludgeon / 3) * ABBYBLUDGEON;
		gp += counter * SIRESTANDARD;

		if (option == 1)
		{
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total abby heads: " << head << '\n';
			std::cout << "Total whips: " << whip << '\n';
			std::cout << "Total bludgeons: " << bludgeon / 3 << "(" << bludgeon % 3 << ")" << '\n';
			std::cout << "Total daggers: " << dagger << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Gp earned: " << gp << '\n';
		}

		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clues;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int roll = rand() % 100 + 1;
			if (roll == 1)
			{
				int rare = rand() % 128 + 1;
				if (rare < 14)
					jar++;
				else if (rare > 13 && rare < 24)
					head++;
				else if (rare > 23 && rare < 36)
					whip++;
				else if (rare > 35 && rare < 98)
					bludgeon++;
				else if (rare > 97 && rare < 124)
					dagger++;
				else if (rare > 123)
					pet++;
			}
			counter++;
			int clueRoll = rand() % 180;
			if (clueRoll == 1)
				clues++;
		}

		gp += whip * WHIP;
		gp += dagger * ABBYDAGGER;
		gp += (bludgeon / 3) * ABBYBLUDGEON;
		gp += counter * SIRESTANDARD;

		if (option == 1)
		{
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total abby heads: " << head << '\n';
			std::cout << "Total whips: " << whip << '\n';
			std::cout << "Total bludgeons: " << bludgeon / 3 << "(" << bludgeon % 3 << ")" << '\n';
			std::cout << "Total daggers: " << dagger << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clues;
		return returnCounters;
	}
}

clueBox wintertodt(int option, bool petOnly)
{
	int phoenix = 0, tome = 0, burntPage = 0, pyroTop = 0, pyroBottom = 0, pyroHood = 0, pyroBoots = 0, pyroGloves = 0, brumaTorch = 0, extraBurntPage = 0;
	long long int gp = 0;
	double counter = 0;
	if (petOnly == 0)
	{
		while (phoenix == 0 || tome == 0 || burntPage == 0 || pyroTop == 0 || pyroBottom == 0 || pyroHood == 0 || pyroBoots == 0 || pyroGloves == 0
			|| brumaTorch == 0)
		{
			int pet = rand() % 100 + 1;
			int roll = rand() % 10 + 1;
			if (pet == 1)
			{
				int pet2 = rand() % 50 + 1;
				if (pet2 == 1)
					phoenix++;
			}
			if (roll == 1)
			{
				int rareRoll = rand() % 300 + 1;
				if (rareRoll < 21)
					pyroGloves++;
				else if (rareRoll > 20 && rareRoll < 41)
					brumaTorch++;
				else if (rareRoll > 40 && rareRoll < 61)
					pyroHood++;
				else if (rareRoll > 60 && rareRoll < 81)
					pyroTop++;
				else if (rareRoll > 80 && rareRoll < 101)
					pyroBoots++;
				else if (rareRoll > 100 && rareRoll < 121)
					pyroBottom++;
				else if (rareRoll > 120 && rareRoll < 124)
					tome++;
			}
			else if (roll == 2)
			{
				int pageRoll = rand() % 9 + 1;
				if (pageRoll < 3)
					burntPage += rand() % 27 + 7;
			}
			counter++;
		}

		int extraBurntPage = pyroGloves * 50 + pyroHood * 50 + pyroBoots * 50 + pyroTop * 50 + pyroBottom * 50 + brumaTorch * 50;
		gp += burntPage * BURNTPAGE;
		gp += extraBurntPage * BURNTPAGE;
		gp += counter * WINTERTODTSTANDARD;

		if (option == 1)
		{
			std::cout << "Total warm gloves: " << pyroGloves << '\n';
			std::cout << "Total bruma torches: " << brumaTorch << '\n';
			std::cout << "Total pyro hoods: " << pyroHood << '\n';
			std::cout << "Total pyro tops: " << pyroTop << '\n';
			std::cout << "Total pyro bottoms: " << pyroBottom << '\n';
			std::cout << "Total pyro boots: " << pyroBoots << '\n';
			std::cout << "Total tomes: " << tome << '\n';
			std::cout << "Total burnt pages: " << burntPage << '\n';
			std::cout << "Total phoenix pets: " << phoenix << '\n';
			std::cout << "Total kills: " << ceil(counter / 28) << '\n';
			std::cout << "Gp gained: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = ceil(counter / 28);
		returnCounters.return2 = gp;
		return returnCounters;
	}
	else
	{
		while (phoenix == 0)
		{
			int pet = rand() % 5000 + 1;
			int roll = rand() % 10 + 1;
			if (pet == 1)
				phoenix++;
			if (roll == 1)
			{
				int rareRoll = rand() % 300 + 1;
				if (rareRoll < 21)
					pyroGloves++;
				else if (rareRoll > 20 && rareRoll < 41)
					brumaTorch++;
				else if (rareRoll > 40 && rareRoll < 61)
					pyroHood++;
				else if (rareRoll > 60 && rareRoll < 81)
					pyroTop++;
				else if (rareRoll > 80 && rareRoll < 101)
					pyroBoots++;
				else if (rareRoll > 100 && rareRoll < 121)
					pyroBottom++;
				else if (rareRoll > 120 && rareRoll < 124)
					tome++;
			}
			else if (roll == 2)
			{
				int pageRoll = rand() % 9 + 1;
				if (pageRoll < 3)
					burntPage += rand() % 27 + 7;
			}
			counter++;
		}

		int extraBurntPage = pyroGloves * 50 + pyroHood * 50 + pyroBoots * 50 + pyroTop * 50 + pyroBottom * 50 + brumaTorch * 50;
		gp += burntPage * BURNTPAGE;
		gp += extraBurntPage * BURNTPAGE;
		gp += counter * WINTERTODTSTANDARD;

		if (option == 1)
		{
			std::cout << "Total warm gloves: " << pyroGloves << '\n';
			std::cout << "Total bruma torches: " << brumaTorch << '\n';
			std::cout << "Total pyro hoods: " << pyroHood << '\n';
			std::cout << "Total pyro tops: " << pyroTop << '\n';
			std::cout << "Total pyro bottoms: " << pyroBottom << '\n';
			std::cout << "Total pyro boots: " << pyroBoots << '\n';
			std::cout << "Total tomes: " << tome << '\n';
			std::cout << "Total burnt pages: " << burntPage << '\n';
			std::cout << "Total phoenix pets: " << phoenix << '\n';
			std::cout << "Total kills: " << ceil(counter / 28) << '\n';
			std::cout << "Gp gained: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = ceil(counter / 28);
		returnCounters.return2 = gp;
		return returnCounters;
	}
}

int bryophyta(int option)
{
	int ess = 0, counter = 0;
	while (ess == 0)
	{
		int roll = rand() % 118 + 1;
		if (roll == 1)
			ess++;
		counter++;
	}
	if (option == 1)
	{
		std::cout << "Total kills: " << counter << '\n';
		std::cout << "Total essences: " << ess << '\n';
	}
	return counter;
}

clueBox zulrah(int option, bool petOnly)
{
	double counter = 0;
	int pet = 0, tanzMut = 0, magMut = 0, jar = 0, magic = 0, tanz = 0, serp = 0, tele = 0, onyx = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pet == 0 || tanzMut == 0 || magMut == 0 || jar == 0 || magic == 0 || tanz == 0 || serp == 0 ||
			tele == 0 || onyx == 0)
		{
			int roll = rand() % 256 + 1;
			int petRoll = rand() % 400 + 1;
			if (roll < 256)
			{
				int flaxRoll = rand() % 249 + 1;
				if (flaxRoll < 11)
				{
					int mutRoll = rand() % 1316 + 1;
					if (mutRoll < 6)
					{
						int color = rand() % 2;
						if (color == 0)
							tanzMut++;
						else
							magMut++;
					}
				}
				else if (flaxRoll > 10 && flaxRoll < 27)
					tele += 4;
				else if (flaxRoll == 249)
				{
					int jarRoll = rand() % 6 + 1;
					if (jarRoll == 1)
						jar++;
				}
			}
			else if (roll == 256)
			{
				int rareRoll = rand() % 4 + 1;
				if (rareRoll == 1)
					tanz++;
				else if (rareRoll == 2)
					magic++;
				else if (rareRoll == 3)
					serp++;
				else if (rareRoll == 4)
					onyx++;
			}
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 20 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			counter++;
			int clueRoll = rand() % 75;
			if (clueRoll == 1)
				clue++;
		}

		gp += onyx * ONYX;
		gp += tanz * TANZFANG;
		gp += magic * MAGICFANG;
		gp += serp * SERPVISAGE;
		gp += counter * ZULRAHSTANDARD;

		if (option == 1)
		{
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total tanz mutagens: " << tanzMut << '\n';
			std::cout << "Total magma mutagens: " << magMut << '\n';
			std::cout << "Total onyx: " << onyx << '\n';
			std::cout << "Total blowpipe: " << tanz << '\n';
			std::cout << "Total serp helms: " << serp << '\n';
			std::cout << "Total magic fang: " << magic << '\n';
			std::cout << "Total teles: " << tele << '\n';
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total kills: " << ceil(counter / 2) << '\n';
			std::cout << "Total gp gained: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int roll = rand() % 256 + 1;
			int petRoll = rand() % 8000 + 1;
			if (roll < 256)
			{
				int flaxRoll = rand() % 249 + 1;
				if (flaxRoll < 11)
				{
					int mutRoll = rand() % 1316 + 1;
					if (mutRoll < 6)
					{
						int color = rand() % 2;
						if (color == 0)
							tanzMut++;
						else
							magMut++;
					}
				}
				else if (flaxRoll > 10 && flaxRoll < 27)
					tele += 4;
				else if (flaxRoll == 249)
				{
					int jarRoll = rand() % 6 + 1;
					if (jarRoll == 1)
						jar++;
				}
			}
			else if (roll == 256)
			{
				int rareRoll = rand() % 4 + 1;
				if (rareRoll == 1)
					tanz++;
				else if (rareRoll == 2)
					magic++;
				else if (rareRoll == 3)
					serp++;
				else if (rareRoll == 4)
					onyx++;
			}
			if (petRoll == 1)
				pet++;
			counter++;

			int clueRoll = rand() % 75;
			if (clueRoll == 1)
				clue++;
		}

		gp += onyx * ONYX;
		gp += tanz * TANZFANG;
		gp += magic * MAGICFANG;
		gp += serp * SERPVISAGE;
		gp += counter * ZULRAHSTANDARD;

		if (option == 1)
		{
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total tanz mutagens: " << tanzMut << '\n';
			std::cout << "Total magma mutagens: " << magMut << '\n';
			std::cout << "Total onyx: " << onyx << '\n';
			std::cout << "Total blowpipe: " << tanz << '\n';
			std::cout << "Total serp helms: " << serp << '\n';
			std::cout << "Total magic fang: " << magic << '\n';
			std::cout << "Total teles: " << tele << '\n';
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total kills: " << ceil(counter / 2) << '\n';
			std::cout << "Total gp gained: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

dagBox dags(int option, bool petOnly)
{
	double rexCounter = 0, primeCounter = 0, supCounter = 0, counter = 0, gp = 0;
	int rex = 0, supreme = 0, prime = 0, bers = 0, arch = 0, seer = 0, warr = 0, axe = 0, seercull = 0, mud = 0, rotation = 0, clue = 0;
	if (petOnly == 0)
	{
		while (rex == 0 || supreme == 0 || prime == 0 || bers == 0 || arch == 0 || seer == 0 || warr == 0 || axe == 0 || seercull == 0 || mud == 0)
		{
			if (rotation == 0)
			{
				if (rex < 1)
					rexCounter++;
				int roll = rand() % 32 + 1;
				int petRoll = rand() % 100 + 1;
				if (roll == 1)
				{
					int innerRoll = rand() % 4 + 1;
					if (innerRoll == 1)
						bers++;
					else if (innerRoll == 2)
						warr++;
					else if (innerRoll == 3)
						axe++;
				}
				if (petRoll == 1)
				{
					int petRoll2 = rand() % 50 + 1;
					if (petRoll2 == 1)
						rex++;
				}
			}
			else if (rotation == 1)
			{
				if (supreme < 1)
					supCounter++;
				int roll = rand() % 32 + 1;
				int petRoll = rand() % 100 + 1;
				if (roll == 1)
				{
					int innerRoll = rand() % 4 + 1;
					if (innerRoll == 1)
						arch++;
					else if (innerRoll == 2)
						seercull++;
					else if (innerRoll == 3)
						axe++;
				}
				if (petRoll == 1)
				{
					int petRoll2 = rand() % 50 + 1;
					if (petRoll2 == 1)
						supreme++;
				}
			}

			else if (rotation == 2)
			{
				if (prime < 1)
					primeCounter++;
				int roll = rand() % 32 + 1;
				int petRoll = rand() % 100 + 1;
				if (roll == 1)
				{
					int innerRoll = rand() % 4 + 1;
					if (innerRoll == 1)
						seer++;
					else if (innerRoll == 2)
						mud++;
					else if (innerRoll == 3)
						axe++;
				}
				if (petRoll == 1)
				{
					int petRoll2 = rand() % 50 + 1;
					if (petRoll2 == 1)
						prime++;
				}
			}
			if (rotation == 0)
				rotation = 1;
			else if (rotation == 1)
				rotation = 2;
			else if (rotation == 2)
				rotation = 0;
			counter++;
			int clueRoll = rand() % 750;
			if (clueRoll == 1)
				clue++;
		}

		gp += (counter / 3) * REXSTANDARD;
		gp += (counter / 3) * SUPREMESTANDARD;
		gp += (counter / 3) * PRIMESTANDARD;
		gp += bers * ZERKRING;
		gp += warr * WARRIORRING;
		gp += seer * SEERRING;
		gp += arch * ARCHERRING;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "First rex obtained at: " << rexCounter << '\n';
			std::cout << "First supreme obtianed at: " << supCounter << '\n';
			std::cout << "first prime obtained at: " << primeCounter << '\n';
			std::cout << "Total berserker rings: " << bers << '\n';
			std::cout << "Total warrior rings: " << warr << '\n';
			std::cout << "Total seers rings: " << seer << '\n';
			std::cout << "Total mud battlestaves: " << mud << '\n';
			std::cout << "Total archer rings: " << arch << '\n';
			std::cout << "Total seerculls: " << seercull << '\n';
			std::cout << "Total dragon axes: " << axe << '\n';
			std::cout << "Total rex pets: " << rex << '\n';
			std::cout << "Total supreme pets: " << supreme << '\n';
			std::cout << "Total prime pets: " << prime << '\n';
			std::cout << "Total gp gained: " << gp << '\n';
		}
		dagBox returnCounters;
		returnCounters.rex1 = rexCounter;
		returnCounters.supreme1 = supCounter;
		returnCounters.prime1= primeCounter;
		returnCounters.gp = gp;
		returnCounters.clue = clue;
		return returnCounters;
	}
	else
	{
		while (rex == 0 || supreme == 0 || prime == 0)
		{
			if (rotation == 0)
			{
				if (rex < 1)
					rexCounter++;
				int roll = rand() % 32 + 1;
				int petRoll = rand() % 100 + 1;
				if (roll == 1)
				{
					int innerRoll = rand() % 4 + 1;
					if (innerRoll == 1)
						bers++;
					else if (innerRoll == 2)
						warr++;
					else if (innerRoll == 3)
						axe++;
				}
				if (petRoll == 1)
				{
					int petRoll2 = rand() % 50 + 1;
					if (petRoll2 == 1)
						rex++;
				}
			}
			else if (rotation == 1)
			{
				if (supreme < 1)
					supCounter++;
				int roll = rand() % 32 + 1;
				int petRoll = rand() % 100 + 1;
				if (roll == 1)
				{
					int innerRoll = rand() % 4 + 1;
					if (innerRoll == 1)
						arch++;
					else if (innerRoll == 2)
						seercull++;
					else if (innerRoll == 3)
						axe++;
				}
				if (petRoll == 1)
				{
					int petRoll2 = rand() % 50 + 1;
					if (petRoll2 == 1)
						supreme++;
				}
			}

			else if (rotation == 2)
			{
				if (prime < 1)
					primeCounter++;
				int roll = rand() % 32 + 1;
				int petRoll = rand() % 100 + 1;
				if (roll == 1)
				{
					int innerRoll = rand() % 4 + 1;
					if (innerRoll == 1)
						seer++;
					else if (innerRoll == 2)
						mud++;
					else if (innerRoll == 3)
						axe++;
				}
				if (petRoll == 1)
				{
					int petRoll2 = rand() % 50 + 1;
					if (petRoll2 == 1)
						prime++;
				}
			}
			if (rotation == 0)
				rotation = 1;
			else if (rotation == 1)
				rotation = 2;
			else if (rotation == 2)
				rotation = 0;
			counter++;
			int clueRoll = rand() % 750;
			if (clueRoll == 1)
				clue++;
		}

		gp += (counter / 3) * REXSTANDARD;
		gp += (counter / 3) * SUPREMESTANDARD;
		gp += (counter / 3) * PRIMESTANDARD;
		gp += bers * ZERKRING;
		gp += warr * WARRIORRING;
		gp += seer * SEERRING;
		gp += arch * ARCHERRING;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "First rex obtained at: " << rexCounter << '\n';
			std::cout << "First supreme obtianed at: " << supCounter << '\n';
			std::cout << "first prime obtained at: " << primeCounter << '\n';
			std::cout << "Total berserker rings: " << bers << '\n';
			std::cout << "Total warrior rings: " << warr << '\n';
			std::cout << "Total seers rings: " << seer << '\n';
			std::cout << "Total mud battlestaves: " << mud << '\n';
			std::cout << "Total archer rings: " << arch << '\n';
			std::cout << "Total seerculls: " << seercull << '\n';
			std::cout << "Total dragon axes: " << axe << '\n';
			std::cout << "Total rex pets: " << rex << '\n';
			std::cout << "Total supreme pets: " << supreme << '\n';
			std::cout << "Total prime pets: " << prime << '\n';
			std::cout << "Total gp gained: " << gp << '\n';
		}
		dagBox returnCounters;
		returnCounters.rex1 = rexCounter;
		returnCounters.supreme1 = supCounter;
		returnCounters.prime1 = primeCounter;
		returnCounters.gp = gp;
		returnCounters.clue = clue;
		return returnCounters;
	}
}

clueBox corp(int option, bool petOnly)
{
	int counter = 0, pet = 0, ely = 0, spec = 0, arc = 0, elixir = 0, shield = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pet == 0 || ely == 0 || spec == 0 || arc == 0 || elixir == 0 || shield == 0)
		{
			int roll = rand() % 585 + 1;
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			if (roll < 10)
				shield++;
			else if (roll > 9 && roll < 13) // shields and elixirs not completely accurate, fix in future if have time
				elixir++;
			else if (roll == 585)
			{
				int sigilRoll = rand() % 7 + 1;
				if (sigilRoll < 4)
					arc++;
				else if (sigilRoll > 3 && sigilRoll < 7)
					spec++;
				else if (sigilRoll == 7)
					ely++;
			}
			counter++;
			int clueRoll = rand() % 200;
			if (clueRoll == 1)
				clue++;
		}

		gp += ely * ELYSIAN;
		gp += arc * ARCANE;
		gp += spec * SPECTRAL;
		gp += CORPSTANDARD * counter;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total elysian sigils: " << ely << '\n';
			std::cout << "Total arcane sigils: " << arc << '\n';
			std::cout << "Total spectral sigils: " << spec << '\n';
			std::cout << "Total elixirs: " << elixir << '\n';
			std::cout << "Total spirit shields: " << shield << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int roll = rand() % 585 + 1;
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			if (roll < 10)
				shield++;
			else if (roll > 9 && roll < 13) // shields and elixirs not completely accurate, fix in future if have time
				elixir++;
			else if (roll == 585)
			{
				int sigilRoll = rand() % 7 + 1;
				if (sigilRoll < 4)
					arc++;
				else if (sigilRoll > 3 && sigilRoll < 7)
					spec++;
				else if (sigilRoll == 7)
					ely++;
			}
			counter++;
			int clueRoll = rand() % 200;
			if (clueRoll == 1)
				clue++;
		}

		gp += ely * ELYSIAN;
		gp += arc * ARCANE;
		gp += spec * SPECTRAL;
		gp += CORPSTANDARD * counter;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total elysian sigils: " << ely << '\n';
			std::cout << "Total arcane sigils: " << arc << '\n';
			std::cout << "Total spectral sigils: " << spec << '\n';
			std::cout << "Total elixirs: " << elixir << '\n';
			std::cout << "Total spirit shields: " << shield << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox vorkath(int option, bool petOnly)
{
	int counter = 0, pet = 0, jar = 0, drac = 0, skele = 0, bone = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pet == 0 || jar == 0 || skele == 0 || bone == 0)
		{
			int roll = rand() % 100 + 1;
			int petRoll = rand() % 300 + 1;
			if (roll == 1)
			{
				int rareRoll = rand() % 150 + 1;
				if (rareRoll < 6)
					jar++;
				else if (rareRoll > 5 && rareRoll < 9)
					drac++;
				else if (rareRoll > 8 && rareRoll < 12)
					skele++;
				else if (rareRoll > 11 && rareRoll < 27)
					bone++;
			}
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 10 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			counter++;
			int clueRoll = rand() % 65;
			if (clueRoll == 1)
				clue++;
		}

		gp += VORKSTANDARD * counter;
		gp += skele * SKELETALVISAGE;
		gp += drac * DRACONICVISAGE;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total draconic visages: " << drac << '\n';
			std::cout << "Total skeletal visages: " << skele << '\n';
			std::cout << "Total dragonbone necklaces: " << bone << '\n';
			std::cout << "Total gp gain: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int roll = rand() % 100 + 1;
			int petRoll = rand() % 3000 + 1;
			if (roll == 1)
			{
				int rareRoll = rand() % 150 + 1;
				if (rareRoll < 6)
					jar++;
				else if (rareRoll > 5 && rareRoll < 9)
					drac++;
				else if (rareRoll > 8 && rareRoll < 12)
					skele++;
				else if (rareRoll > 11 && rareRoll < 27)
					bone++;
			}
			if (petRoll == 3000)
				pet++;
			counter++;
			int clueRoll = rand() % 65;
			if (clueRoll == 1)
				clue++;
		}

		gp += VORKSTANDARD * counter;
		gp += skele * SKELETALVISAGE;
		gp += drac * DRACONICVISAGE;

		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total draconic visages: " << drac << '\n';
			std::cout << "Total skeletal visages: " << skele << '\n';
			std::cout << "Total dragonbone necklaces: " << bone << '\n';
			std::cout << "Total gp gain: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

int beginnerClue(int option)
{
	double counter = 0;
	int moleSlippers = 0, frogSlippers = 0, bearFeet = 0, demonFeet = 0, jesterCape = 0, shoulderParrot = 0, monkTop = 0, monkBottom = 0, def = 0, hat = 0, sandTop = 0,
		sandBottom = 0, guthix = 0, sara = 0, zam = 0;
	while (moleSlippers == 0 || frogSlippers == 0 || bearFeet == 0 || demonFeet == 0 || jesterCape == 0 || shoulderParrot == 0 || monkTop == 0 || monkBottom == 0 || def == 0 ||
		hat == 0 || sandTop == 0 || sandBottom == 0 || guthix == 0 || sara == 0 || zam == 0)
	{
		int roll = rand() % 25 + 1;
		if (roll == 1)
		{
			int rareRoll = rand() % 15 + 1;
			switch (rareRoll)
			{
			case 1: moleSlippers++;
				break;
			case 2: frogSlippers++;
				break;
			case 3: bearFeet++;
				break;
			case 4: demonFeet++;
				break;
			case 5: jesterCape++;
				break;
			case 6: shoulderParrot++;
				break;
			case 7: monkTop++;
				break;
			case 8: monkBottom++;
				break;
			case 9: def++;
				break;
			case 10: hat++;
				break;
			case 11: sandTop++;
				break;
			case 12: sandBottom++;
				break;
			case 13: guthix++;
				break;
			case 14: sara++;
				break;
			case 15: zam++;
				break;
			}
		}
		counter++;
	}
	if (option == 1)
	{
		std::cout << "Total beginner clues: " << ceil(counter / 2) << '\n';
		std::cout << "Total mole slippers: " << moleSlippers << '\n';
		std::cout << "Total frog slippers: " << frogSlippers << '\n';
		std::cout << "Total bear feet: " << bearFeet << '\n';
		std::cout << "Total demon feet: " << demonFeet << '\n';
		std::cout << "Total jester capes: " << jesterCape << '\n';
		std::cout << "Total shoulder parrots: " << shoulderParrot << '\n';
		std::cout << "Total monk robe tops: " << monkTop << '\n';
		std::cout << "Total monk robebottoms: " << monkBottom << '\n';
		std::cout << "Total defence amulets(t): " << def << '\n';
		std::cout << "Total sandwich lady hats: " << hat << '\n';
		std::cout << "Total sandwich lady tops: " << sandTop << '\n';
		std::cout << "Total sandwich lady bottoms: " << sandBottom << '\n';
		std::cout << "Total rune scimmy guthix kits: " << guthix << '\n';
		std::cout << "Total rune scimmy sara kits: " << sara << '\n';
		std::cout << "Total rune scimmy zammy kits: " << zam << '\n';
	}
	return ceil(counter / 2);
}

clueBox easyClue(int option)
{
	double counter = 0, monkCount = 0, capeCount = 0;
	int woodShieldG = 0, blackFullT = 0, blackPlateT = 0, blackLegsT = 0, blackSkirtT = 0, blackKiteT = 0, blackFullG = 0, blackPlateG = 0, blackLegsG = 0, blackSkirtG = 0, blacKiteG = 0,
		blackH1 = 0, blackH2 = 0, blackH3 = 0, blackH4 = 0, blackH5 = 0, bucket1 = 0, bucket2 = 0, bucket3 = 0, bucket4 = 0, bucket5 = 0, plate1 = 0, plate2 = 0, plate3 = 0, plate4 = 0,
		plate5 = 0, steelFullT = 0, steelPlateT = 0, steelLegsT = 0, steelSkirtT = 0, steelKiteT = 0, steelFullG = 0, steelPlateG = 0, steelLegsG = 0, steelSkirtG = 0, steelKiteG = 0,
		ironFullT = 0, ironPlateT = 0, ironLegsT = 0, ironSkirtT = 0, ironKiteT = 0, ironFullG = 0, ironPlateG = 0, ironLegsG = 0, ironSkirtG = 0, ironKiteG = 0, bronzeFullT = 0, bronzePlateT = 0,
		bronzeLegsT = 0, bronzeSkirtT = 0, bronzeKiteT = 0, bronzeFullG = 0, bronzePlateG = 0, bronzeLegsG = 0, bronzeSkirtG = 0, bronzeKiteG = 0, studdedG = 0, studChapsG = 0, studdedT = 0,
		studChapsT = 0, leatherG = 0, chapsG = 0, blueHatG = 0, blueTopG = 0, blueSkirtG = 0, blueHatT = 0, blueTopT = 0, blueSkirtT = 0, blackHatG = 0, blackTopG = 0, blackRobeSkirtG = 0,
		blackHatT = 0, blackTopT = 0, blackRobeSkirtT = 0, saraTop = 0, saraLegs = 0, guthixTop = 0, guthixLegs = 0, zamTop = 0, zamLegs = 0, ancientTop = 0, ancientLegs = 0, armadylTop = 0,
		armadylLegs = 0, bandosTop = 0, bandosLegs = 0, bobRed = 0, bobGreen = 0, bobBlue = 0, bobBlack = 0, bobPurple = 0, highway = 0, blueBeret = 0, blackBeret = 0, redBeret = 0, whiteBeret = 0,
		wig = 0, beanie = 0, imp = 0, goblin = 0, sleep = 0, flared = 0, pantaloons = 0, blackCane = 0, staffBob = 0, powerT = 0, ham = 0, rainBow = 0, goldChef = 0, goldApron = 0, redEleShirt = 0,
		redEleBlouse = 0, redEleLegs = 0, redEleSkirt = 0, greenEleShirt = 0, greenEleBlouse = 0, greenEleLegs = 0, greenEleSkirt = 0, blueEleShirt = 0, blueEleblouse = 0, blueEleLegs = 0,
		blueEleSkirt = 0, teamZero = 0, teamI = 0, teamX = 0, skulls = 0, monkTopG = 0, monkBottomG = 0;
	while (woodShieldG == 0 || blackFullT == 0 || blackPlateT == 0 || blackLegsT == 0 || blackSkirtT == 0 || blackKiteT == 0 || blackFullG == 0 || blackPlateG == 0 || blackLegsG == 0 || blackSkirtG == 0 || blacKiteG == 0 ||
		blackH1 == 0 || blackH2 == 0 || blackH3 == 0 || blackH4 == 0 || blackH5 == 0 || bucket1 == 0 || bucket2 == 0 || bucket3 == 0 || bucket4 == 0 || bucket5 == 0 || plate1 == 0 || plate2 == 0 || plate3 == 0 || plate4 == 0 ||
		plate5 == 0 || steelFullT == 0 || steelPlateT == 0 || steelLegsT == 0 || steelSkirtT == 0 || steelKiteT == 0 || steelFullG == 0 || steelPlateG == 0 || steelLegsG == 0 || steelSkirtG == 0 || steelKiteG == 0 ||
		ironFullT == 0 || ironPlateT == 0 || ironLegsT == 0 || ironSkirtT == 0 || ironKiteT == 0 || ironFullG == 0 || ironPlateG == 0 || ironLegsG == 0 || ironSkirtG == 0 || ironKiteG == 0 || bronzeFullT == 0 || bronzePlateT == 0 ||
		bronzeLegsT == 0 || bronzeSkirtT == 0 || bronzeKiteT == 0 || bronzeFullG == 0 || bronzePlateG == 0 || bronzeLegsG == 0 || bronzeSkirtG == 0 || bronzeKiteG == 0 || studdedG == 0 || studChapsG == 0 || studdedT == 0 ||
		studChapsT == 0 || leatherG == 0 || chapsG == 0 || blueHatG == 0 || blueTopG == 0 || blueSkirtG == 0 || blueHatT == 0 || blueTopT == 0 || blueSkirtT == 0 || blackHatG == 0 || blackTopG == 0 || blackRobeSkirtG == 0 ||
		blackHatT == 0 || blackTopT == 0 || blackRobeSkirtT == 0 || saraTop == 0 || saraLegs == 0 || guthixTop == 0 || guthixLegs == 0 || zamTop == 0 || zamLegs == 0 || ancientTop == 0 || ancientLegs == 0 || armadylTop == 0 ||
		armadylLegs == 0 || bandosTop == 0 || bandosLegs == 0 || bobRed == 0 || bobGreen == 0 || bobBlue == 0 || bobBlack == 0 || bobPurple == 0 || highway == 0 || blueBeret == 0 || blackBeret == 0 || redBeret == 0 || whiteBeret == 0 ||
		wig == 0 || beanie == 0 || imp == 0 || goblin == 0 || sleep == 0 || flared == 0 || pantaloons == 0 || blackCane == 0 || staffBob == 0 || powerT == 0 || ham == 0 || rainBow == 0 || goldChef == 0 || goldApron == 0 || redEleShirt == 0 ||
		redEleBlouse == 0 || redEleLegs == 0 || redEleSkirt == 0 || greenEleShirt == 0 || greenEleBlouse == 0 || greenEleLegs == 0 || greenEleSkirt == 0 || blueEleShirt == 0 || blueEleblouse == 0 || blueEleLegs == 0 ||
		blueEleSkirt == 0 || teamZero == 0 || teamI == 0 || teamX == 0 || skulls == 0 || monkTopG == 0 || monkBottomG == 0 )
	{
		int roll = rand() % 12 + 1;
		if (roll < 12)
		{
			int standRoll = rand() % 33 + 1;
			if (standRoll == 28)
			{
				int amuletRoll = rand() % 10 + 1;
				if (amuletRoll == 1)
					amuletRoll++;
			}
		}
		else if (roll == 12)
		{
			int rareRoll = rand() % 117 + 1;
			switch (rareRoll)
			{
			case 1: blackPlateT++;
				break;
			case 2: blackLegsT++;
				break;
			case 3: blackFullT++;
				break;
			case 4: blackKiteT++;
				break;
			case 5: blackPlateG++;
				break;
			case 6: blackLegsG++;
				break;
			case 7: blackFullG++;
				break;
			case 8: blacKiteG++;
				break;
			case 9: highway++;
				break;
			case 10: blueBeret++;
				break;
			case 11: blackBeret++;
				break;
			case 12: whiteBeret++;
				break;
			case 13: blackSkirtT++;
				break;
			case 14: blackSkirtG++;
				break;
			case 15: blackH1++;
				break;
			case 16: blackH2++;
				break;
			case 17: blackH3++;
				break;
			case 18: blackH4++;
				break;
			case 19: blackH5++;
				break;
			case 20: studdedG++;
				break;
			case 21: studdedT++;
				break;
			case 22: studChapsG++;
				break;
			case 23: studChapsT++;
				break;
			case 24: blueSkirtG++;
				break;
			case 25: blueSkirtT++;
				break;
			case 26: blueTopG++;
				break;
			case 27: blueTopT++;
				break;
			case 28: blueHatG++;
				break;
			case 29: blueHatT++;
				break;
			case 30: bucket1++;
				break;
			case 31: bucket2++;
				break;
			case 32: bucket3++;
				break;
			case 33: bucket4++;
				break;
			case 34: bucket5++;
				break;
			case 35: bobRed++;
				break;
			case 36: bobBlue++;
				break;
			case 37: bobGreen++;
				break;
			case 38: bobBlack++;
				break;
			case 39: bobPurple++;
				break;
			case 40: wig++;
				break;
			case 41: flared++;
				break;
			case 42: pantaloons++;
				break;
			case 43: sleep++;
				break;
			case 44: saraTop++;
				break;
			case 45: saraLegs++;
				break;
			case 46: guthixTop++;
				break;
			case 47: guthixLegs++;
				break;
			case 48: zamTop++;
				break;
			case 49: zamLegs++;
				break;
			case 50: bronzePlateT++;
				break;
			case 51: bronzeLegsT++;
				break;
			case 52: bronzeSkirtT++;
				break;
			case 53: bronzeKiteT++;
				break;
			case 54: bronzeFullT++;
				break;
			case 55: bronzePlateG++;
				break;
			case 56: bronzeLegsG++;
				break;
			case 57: bronzeSkirtG++;
				break;
			case 58: bronzeKiteG++;
				break;
			case 59: bronzeFullG++;
				break;
			case 60: ironPlateT++;
				break;
			case 61: ironLegsT++;
				break;
			case 62: ironSkirtT++;
				break;
			case 63: ironFullT++;
				break;
			case 64: ironKiteT++;
				break;
			case 65: ironPlateG++;
				break;
			case 66: ironLegsG++;
				break;
			case 67: ironSkirtG++;
				break;
			case 68: ironKiteG++;
				break;
			case 69: ironFullG++;
				break;
			case 70: beanie++;
				break;
			case 71: imp++;
				break;
			case 72: goblin++;
				break;
			case 73: ancientTop++;
				break;
			case 74: ancientLegs++;
				break;
			case 75: armadylTop++;
				break;
			case 76: armadylLegs++;
				break;
			case 77: bandosTop++;
				break;
			case 78: bandosLegs++;
				break;
			case 79: blackCane++;
				break;
			case 80: blackHatG++;
				break;
			case 81: blackTopG++;
				break;
			case 82: blackRobeSkirtG++;
				break;
			case 83: blackHatT++;
				break;
			case 84: blackTopT++;
				break;
			case 85: blackRobeSkirtT++;
				break;
			case 86: woodShieldG++;
				break;
			case 87: steelFullT++;
				break;
			case 88: steelPlateT++;
				break;
			case 89: steelLegsT++;
				break;
			case 90: steelSkirtT++;
				break;
			case 91: steelKiteT++;
				break;
			case 92: steelFullG++;
				break;
			case 93: steelPlateG++;
				break;
			case 94: steelLegsG++;
				break;
			case 95: steelSkirtG++;
				break;
			case 96: steelKiteG++;
				break;
			case 97: redBeret++;
				break;
			case 98: powerT++;
				break;
			case 99: rainBow++;
				break;
			case 100: ham++;
				break;
			case 101: staffBob++;
				break;
			case 102: leatherG++;
				break;
			case 103: chapsG++;
				break;
			case 104: plate1++;
				break;
			case 105: plate2++;
				break;
			case 106: plate3++;
				break;
			case 107: plate4++;
				break;
			case 108: plate5++;
				break;
			case 109:
			{
				int chefRoll = rand() % 2 + 1;
				if (chefRoll == 1)
					goldApron++;
				else if (chefRoll == 2)
					goldChef++;
			}
			break;
			case 110:
			{
				int coinRoll = rand() % 5 + 1;
				if (coinRoll == 5)
				{
					monkCount++;
					int monkRoll = rand() % 2 + 1;
					if (monkRoll == 1)
						monkTopG++;
					else if (monkRoll == 2)
						monkBottomG++;
				}
			}
			break;
			case 111:
			{
				capeCount++;
				int capeRoll = rand() % 4 + 1;
				if (capeRoll == 1)
					teamZero++;
				else if (capeRoll == 2)
					teamI++;
				else if (capeRoll == 3)
					teamX++;
				else if (capeRoll == 4)
					skulls++;
			}
			break;
			default:
			{
				int eleRoll = rand() % 12 + 1;
				if (eleRoll == 1)
					redEleShirt++;
				else if (eleRoll == 2)
					redEleLegs++;
				else if (eleRoll == 3)
					redEleBlouse++;
				else if (eleRoll == 4)
					redEleSkirt++;
				else if (eleRoll == 5)
					greenEleShirt++;
				else if (eleRoll == 6)
					greenEleLegs++;
				else if (eleRoll == 7)
					greenEleBlouse++;
				else if (eleRoll == 8)
					greenEleSkirt++;
				else if (eleRoll == 9)
					blueEleShirt++;
				else if (eleRoll == 10)
					blueEleLegs++;
				else if (eleRoll == 11)
					blueEleblouse++;
				else if (eleRoll == 12)
					blueEleSkirt++;
			}
			}
		}
		counter++;
	}
	if (option == 1)
	{
		std::cout << "Total wooden shield g: " << woodShieldG << '\n';
		std::cout << "Total black full helm t: " << blackFullT << '\n';
		std::cout << "Total black platebody t: " << blackPlateT << '\n';
		std::cout << "Total black platelegs t: " << blackLegsT << '\n';
		std::cout << "Total black plateskirt t: " << blackSkirtT << '\n';
		std::cout << "Total black kite t: " << blackKiteT << '\n';
		std::cout << "Total black full helm g: " << blackFullG << '\n';
		std::cout << "Total black paltebody g: " << blackPlateG << '\n';
		std::cout << "Total black platelegs g: " << blackLegsG << '\n';
		std::cout << "Total black plateskirt g: " << blackSkirtG << '\n';
		std::cout << "Total black kite g: " << blacKiteG << '\n';
		std::cout << "Total black shield h1: " << blackH1 << '\n';
		std::cout << "Total black shield h2: " << blackH2 << '\n';
		std::cout << "Total black shield h3: " << blackH3 << '\n';
		std::cout << "Total black shield h4: " << blackH4 << '\n';
		std::cout << "Total black shield h5: " << blackH5 << '\n';
		std::cout << "Total black helm h1: " << bucket1 << '\n';
		std::cout << "Total black helm h2: " << bucket2 << '\n';
		std::cout << "Total black helm h3: " << bucket3 << '\n';
		std::cout << "Total black helm h4: " << bucket4 << '\n';
		std::cout << "Total black helm h5: " << bucket5 << '\n';
		std::cout << "Total black plate h1: " << plate1 << '\n';
		std::cout << "Total black plate h2: " << plate2 << '\n';
		std::cout << "Total black plate h3: " << plate3 << '\n';
		std::cout << "Total black plate h4: " << plate4 << '\n';
		std::cout << "Total black plate h5: " << plate5 << '\n';
		std::cout << "Total steel full helm t: " << steelFullT << '\n';
		std::cout << "Total steel platebody t: " << steelPlateT << '\n';
		std::cout << "Total steel platelegs t: " << steelLegsT << '\n';
		std::cout << "Total steel plateskirt t: " << steelSkirtT << '\n';
		std::cout << "Total steel kite t: " << steelKiteT << '\n';
		std::cout << "Total steel full helm g: " << steelFullG << '\n';
		std::cout << "Total steel platebody g: " << steelPlateG << '\n';
		std::cout << "Total steel platelegs g: " << steelLegsG << '\n';
		std::cout << "Total steel plateskirt g: " << steelSkirtG << '\n';
		std::cout << "Total steel kite g: " << steelKiteG << '\n';
		std::cout << "Total iron full helm t: " << ironFullT << '\n';
		std::cout << "Total iron platebody t: " << ironPlateT << '\n';
		std::cout << "Total iron platelegs t: " << ironLegsT << '\n';
		std::cout << "Total iron plateskirt t: " << ironSkirtT << '\n';
		std::cout << "Total iron kite t: " << ironKiteT << '\n';
		std::cout << "Total iron full helm g: " << ironFullG << '\n';
		std::cout << "Total iron platebody g: " << ironPlateG << '\n';
		std::cout << "Total iron platelegs g: " << ironLegsG << '\n';
		std::cout << "Total iron plateskirt g: " << ironSkirtG << '\n';
		std::cout << "Total iron kite g: " << ironKiteG << '\n';
		std::cout << "Total bronze full helm t: " << bronzeFullT << '\n';
		std::cout << "Total bronze platebody t: " << bronzePlateT << '\n';
		std::cout << "Total bronze platelegs t: " << bronzeLegsT << '\n';
		std::cout << "Total bronze plateskirt t: " << bronzeSkirtT << '\n';
		std::cout << "Total bronze kite t: " << bronzeKiteT << '\n';
		std::cout << "Total bronze full helm g: " << bronzeFullG << '\n';
		std::cout << "Total bronze platebody g: " << bronzePlateG << '\n';
		std::cout << "Total bronze platelegs g: " << bronzeLegsG << '\n';
		std::cout << "Total bronze plateskirt g: " << bronzeSkirtG << '\n';
		std::cout << "Total bronze kite g: " << bronzeKiteG << '\n';
		std::cout << "Total studded body g: " << studdedG << '\n';
		std::cout << "Total studded chaps g: " << studChapsG << '\n';
		std::cout << "Total studded body t: " << studdedT << '\n';
		std::cout << "Total studded chaps t: " << studChapsT << '\n';
		std::cout << "Total leather body g: " << leatherG << '\n';
		std::cout << "Total leather chaps g: " << chapsG << '\n';
		std::cout << "Total blue wizzy hat g: " << blueHatG << '\n';
		std::cout << "Total blue wizzy robetop g: " << blueTopG << '\n';
		std::cout << "Total blue wizzy bottom g: " << blueSkirtG << '\n';
		std::cout << "Total blue wizzy hat t: " << blueHatT << '\n';
		std::cout << "Total blue wizzy robetop t: " << blueTopT << '\n';
		std::cout << "Total blue wizzy robebottom t: " << blueSkirtT << '\n';
		std::cout << "Total black wizzy hat g: " << blackHatG << '\n';
		std::cout << "Total black wizzy robetop g: " << blackTopG << '\n';
		std::cout << "Total black wizzy robebottom g: " << blackSkirtG << '\n';
		std::cout << "Total black wizzy hat t: " << blackHatT << '\n';
		std::cout << "Total black wizzy robetop t: " << blackTopT << '\n';
		std::cout << "Total black wizzy robebottom t: " << blackSkirtT << '\n';
		std::cout << "Total saradomin robe top: " << saraTop << '\n';
		std::cout << "Total saradomin robelegs: " << saraLegs << '\n';
		std::cout << "Total guthix robe top: " << guthixTop << '\n';
		std::cout << "Total guthix robelegs: " << guthixLegs << '\n';
		std::cout << "Total zammy robe top: " << zamTop << '\n';
		std::cout << "Total zammy robelegs: " << zamLegs << '\n';
		std::cout << "Total ancient robetop: " << ancientTop << '\n';
		std::cout << "Total ancient robelegs: " << ancientLegs << '\n';
		std::cout << "Total armadyl robetop: " << armadylTop << '\n';
		std::cout << "Total armadyl robelegs: " << armadylLegs << '\n';
		std::cout << "Total bandos robetop: " << bandosTop << '\n';
		std::cout << "Total bandos robelegs: " << bandosLegs << '\n';
		std::cout << "Total bob's red shirt: " << bobRed << '\n';
		std::cout << "Total bob's green shirt: " << bobGreen << '\n';
		std::cout << "Total bob's blue shirt: " << bobBlue << '\n';
		std::cout << "Total bob's black shirt: " << bobBlack << '\n';
		std::cout << "Total bob's purple shirt: " << bobPurple << '\n';
		std::cout << "Total highwayman mask: " << highway << '\n';
		std::cout << "Total blue beret: " << blueBeret << '\n';
		std::cout << "Total black beret: " << blackBeret << '\n';
		std::cout << "Total red beret: " << redBeret << '\n';
		std::cout << "Total white beret: " << whiteBeret << '\n';
		std::cout << "Total powdered wig: " << wig << '\n';
		std::cout << "Total beanie: " << beanie << '\n';
		std::cout << "Total imp masks: " << imp << '\n';
		std::cout << "Total goblin masks: " << goblin << '\n';
		std::cout << "Total sleeping caps: " << sleep << '\n';
		std::cout << "Total flared trousers: " << flared << '\n';
		std::cout << "Total pantaloons: " << pantaloons << '\n';
		std::cout << "Total black canes: " << blackCane << '\n';
		std::cout << "Total staff of bobs: " << staffBob << '\n';
		std::cout << "Total amulet of power t: " << powerT << '\n';
		std::cout << "Total ham joints: " << ham << '\n';
		std::cout << "Total rain bows: " << rainBow << '\n';
		std::cout << "Total golden chef's hats: " << goldChef << '\n';
		std::cout << "Total golden aprons: " << goldApron << '\n';
		std::cout << "Total red ele shirts: " << redEleShirt << '\n';
		std::cout << "Total red ele blouse: " << redEleBlouse << '\n';
		std::cout << "Total red ele legs: " << redEleLegs << '\n';
		std::cout << "Total red ele skirt: " << redEleSkirt << '\n';
		std::cout << "Total green ele shirts: " << greenEleShirt << '\n';
		std::cout << "Total green ele blouse: " << greenEleBlouse << '\n';
		std::cout << "Total green ele legs: " << greenEleLegs << '\n';
		std::cout << "Total green ele skirts: " << greenEleSkirt << '\n';
		std::cout << "Total blue ele shirt: " << blueEleShirt << '\n';
		std::cout << "Total blue ele blouse: " << blueEleblouse << '\n';
		std::cout << "Total blue ele legs: " << blueEleLegs << '\n';
		std::cout << "Total blue ele skirt: " << blueEleSkirt << '\n';
		std::cout << "Total team cape zero: " << teamZero << '\n';
		std::cout << "Total team cape i: " << teamI << '\n';
		std::cout << "Total team cape x: " << teamX << '\n';
		std::cout << "Total cape of skulls: " << skulls << '\n';
		std::cout << "Total monk robe tops g: " << monkTopG << '\n';
		std::cout << "Total monk robe legs g: " << monkBottomG << '\n';
		std::cout << "Total easy clues completed: " << ceil(counter / 3) << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = ceil(counter / 3);
	returnCounters.return2 = monkCount;
	returnCounters.return3 = capeCount;
	return returnCounters;
}

clueBox mediumClue(int option)
{
	double counter = 0, masterCount = 0;
	int rangerBoots = 0, wizBoots = 0, holySandals = 0, spikedManacles = 0, climbingBoot = 0, addyFullT = 0, addyPlateT = 0, addyLegsT = 0, addySkirtT = 0, addyKiteT = 0, addyFullG = 0,
		addyPlateG = 0, addyLegsG = 0, addySkirtG = 0, addyKiteG = 0, addyShield1 = 0, addyShield2 = 0, addyShield3 = 0, addyShield4 = 0, addyShield5 = 0, bucket1 = 0, bucket2 = 0,
		bucket3 = 0, bucket4 = 0, bucket5 = 0, plate1 = 0, plate2 = 0, plate3 = 0, plate4 = 0, plate5 = 0, mithFullG = 0, mithPlateG = 0, mithLegsG = 0, mithSkirtG = 0, mithKiteG = 0,
		mithFullT = 0, mithPlateT = 0, mithLegsT = 0, mithSkirtT = 0, mithKiteT = 0, greenBodyG = 0, greenBodyT = 0, greenChapsG = 0, greenChapsT = 0, saraMitre = 0, saraCloak = 0,
		guthixMitre = 0, guthixCloak = 0, zamMitre = 0, zamCloak = 0, ancientMitre = 0, ancientCloak = 0, ancientStole = 0, ancientCrozier = 0, armadylMitre = 0, armadylCloak = 0,
		armadylStole = 0, armadylCrozier = 0, bandosMitre = 0, bandosCloak = 0, bandosStole = 0, bandosCrozier = 0, redBoater = 0, greenBoater = 0, orangeBoater = 0, blackBoater = 0,
		blueBoater = 0, pinkBoater = 0, purpleBoater = 0, whiteBoater = 0, redBand = 0, blackBando = 0, brownBand = 0, whiteBand = 0, blueBand = 0, goldBand = 0, pinkBand = 0,
		greenBand = 0, crierHat = 0, addyCane = 0, cat = 0, penguin = 0, lepHat = 0, crierCoat = 0, crierBell = 0, arcBanner = 0, piscBanner = 0, hosBanner = 0, shayBanner = 0,
		lovBanner = 0, cabShield = 0, wolfMask = 0, wolfCloak = 0, blackLepHat = 0, blackUnicorn = 0, whiteUnicorn = 0, purpleShirt = 0, purpleBlouse = 0, purpleLegs = 0, purpleSkirt = 0,
		blackShirt = 0, whiteBlouse = 0, blackLegs = 0, whiteSkirt = 0, pinkShirt = 0, pinkBlouse = 0, pinkLegs = 0, pinkSkirt = 0, goldShirt = 0, goldBlouse = 0, goldLegs = 0, goldSkirt = 0;
	while (rangerBoots == 0 || wizBoots == 0 || holySandals == 0 || spikedManacles == 0 || climbingBoot == 0 || addyFullT == 0 || addyPlateT == 0 || addyLegsT == 0 || addySkirtT == 0 || addyKiteT == 0 || addyFullG == 0 ||
		addyPlateG == 0 || addyLegsG == 0 || addySkirtG == 0 || addyKiteG == 0 || addyShield1 == 0 || addyShield2 == 0 || addyShield3 == 0 || addyShield4 == 0 || addyShield5 == 0 || bucket1 == 0 || bucket2 == 0 ||
		bucket3 == 0 || bucket4 == 0 || bucket5 == 0 || plate1 == 0 || plate2 == 0 || plate3 == 0 || plate4 == 0 || plate5 == 0 || mithFullG == 0 || mithPlateG == 0 || mithLegsG == 0 || mithSkirtG == 0 || mithKiteG == 0 ||
		mithFullT == 0 || mithPlateT == 0 || mithLegsT == 0 || mithSkirtT == 0 || mithKiteT == 0 || greenBodyG == 0 || greenBodyT == 0 || greenChapsG == 0 || greenChapsT == 0 || saraMitre == 0 || saraCloak == 0 ||
		guthixMitre == 0 || guthixCloak == 0 || zamMitre == 0 || zamCloak == 0 || ancientMitre == 0 || ancientCloak == 0 || ancientStole == 0 || ancientCrozier == 0 || armadylMitre == 0 || armadylCloak == 0 ||
		armadylStole == 0 || armadylCrozier == 0 || bandosMitre == 0 || bandosCloak == 0 || bandosStole == 0 || bandosCrozier == 0 || redBoater == 0 || greenBoater == 0 || orangeBoater == 0 || blackBoater == 0 ||
		blueBoater == 0 || pinkBoater == 0 || purpleBoater == 0 || whiteBoater == 0 || redBand == 0 || blackBando == 0 || brownBand == 0 || whiteBand == 0 || blueBand == 0 || goldBand == 0 || pinkBand == 0 ||
		greenBand == 0 || crierHat == 0 || addyCane == 0 || cat == 0 || penguin == 0 || lepHat == 0 || crierCoat == 0 || crierBell == 0 || arcBanner == 0 || piscBanner == 0 || hosBanner == 0 || shayBanner == 0 ||
		lovBanner == 0 || cabShield == 0 || wolfMask == 0 || wolfCloak == 0 || blackLepHat == 0 || blackUnicorn == 0 || whiteUnicorn == 0 || purpleShirt == 0 || purpleBlouse == 0 || purpleLegs == 0 || purpleSkirt == 0 ||
		blackShirt == 0 || whiteBlouse == 0 || blackLegs == 0 || whiteSkirt == 0 || pinkShirt == 0 || pinkBlouse == 0 || pinkLegs == 0 || pinkSkirt == 0 || goldShirt == 0 || goldBlouse == 0 || goldLegs == 0 || goldSkirt == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int roll = rand() % 11 + 1;
			if (roll == 1)
			{
				int rareRoll = rand() % 103 + 1;
				switch (rareRoll)
				{
				case 1: rangerBoots++;
					break;
				case 2: wizBoots++;
					break;
				case 3: holySandals++;
					break;
				case 4: spikedManacles++;
					break;
				case 5: climbingBoot++;
					break;
				case 6: addyFullT++;
					break;
				case 7: addyPlateT++;
					break;
				case 8: addyLegsT++;
					break;
				case 9: addySkirtT++;
					break;
				case 10: addyKiteT++;
					break;
				case 11: addyFullG++;
					break;
				case 12: addyPlateG++;
					break;
				case 13: addyLegsG++;
					break;
				case 14: addySkirtG++;
					break;
				case 15: addyKiteG++;
					break;
				case 16: addyShield1++;
					break;
				case 17: addyShield2++;
					break;
				case 18: addyShield3++;
					break;
				case 19: addyShield4++;
					break;
				case 20: addyShield5++;
					break;
				case 21: bucket1++;
					break;
				case 22: bucket2++;
					break;
				case 23: bucket3++;
					break;
				case 24: bucket4++;
					break;
				case 25: bucket5++;
					break;
				case 26: plate1++;
					break;
				case 27: plate2++;
					break;
				case 28: plate3++;
					break;
				case 29: plate4++;
					break;
				case 30: plate5++;
					break;
				case 31: mithFullG++;
					break;
				case 32: mithPlateG++;
					break;
				case 33: mithLegsG++;
					break;
				case 34: mithSkirtG++;
					break;
				case 35: mithKiteG++;
					break;
				case 36: mithFullT++;
					break;
				case 37: mithPlateT++;
					break;
				case 38: mithLegsT++;
					break;
				case 39: mithSkirtT++;
					break;
				case 40: mithKiteT++;
					break;
				case 41: greenBodyG++;
					break;
				case 42: greenBodyT++;
					break;
				case 43: greenChapsG++;
					break;
				case 44: greenChapsT++;
					break;
				case 45: saraMitre++;
					break;
				case 46: saraCloak++;
					break;
				case 47: guthixMitre++;
					break;
				case 48: guthixCloak++;
					break;
				case 49: zamMitre++;
					break;
				case 50: zamCloak++;
					break;
				case 51: ancientMitre++;
					break;
				case 52: ancientCloak++;
					break;
				case 53: ancientStole++;
					break;
				case 54: ancientCrozier++;
					break;
				case 55: armadylMitre++;
					break;
				case 56: armadylCloak++;
					break;
				case 57: armadylStole++;
					break;
				case 58: armadylCrozier++;
					break;
				case 59: bandosMitre++;
					break;
				case 60: bandosCloak++;
					break;
				case 61: bandosStole++;
					break;
				case 62: bandosCrozier++;
					break;
				case 63: redBoater++;
					break;
				case 64: greenBoater++;
					break;
				case 65: orangeBoater++;
					break;
				case 66: blackBoater++;
					break;
				case 67: blueBoater++;
					break;
				case 68: pinkBoater++;
					break;
				case 69: purpleBoater++;
					break;
				case 70: whiteBoater++;
					break;
				case 71: redBand++;
					break;
				case 72: blackBando++;
					break;
				case 73: brownBand++;
					break;
				case 74: whiteBand++;
					break;
				case 75: blueBand++;
					break;
				case 76: goldBand++;
					break;
				case 77: pinkBand++;
					break;
				case 78: greenBand++;
					break;
				case 79: crierHat++;
					break;
				case 80: addyCane++;
					break;
				case 81: cat++;
					break;
				case 82: penguin++;
					break;
				case 83: lepHat++;
					break;
				case 84: crierCoat++;
					break;
				case 85: crierBell++;
					break;
				case 86: arcBanner++;
					break;
				case 87: piscBanner++;
					break;
				case 88: hosBanner++;
					break;
				case 89: shayBanner++;
					break;
				case 90: lovBanner++;
					break;
				case 91: cabShield++;
					break;
				case 92: wolfMask++;
					break;
				case 93: wolfCloak++;
					break;
				case 94: blackLepHat++;
					break;
				case 95:
				{
					int uniRoll = rand() % 2 + 1;
					if (uniRoll == 1)
						whiteUnicorn++;
					else if (uniRoll == 2)
						blackUnicorn++;
				}
				break;
				default:
				{
					int eleRoll = rand() % 16 + 1;
					if (eleRoll == 1)
						purpleShirt++;
					else if (eleRoll == 2)
						purpleLegs++;
					else if (eleRoll == 3)
						purpleBlouse++;
					else if (eleRoll == 4)
						purpleSkirt++;
					else if (eleRoll == 5)
						blackShirt++;
					else if (eleRoll == 6)
						blackLegs++;
					else if (eleRoll == 7)
						whiteBlouse++;
					else if (eleRoll == 8)
						whiteSkirt++;
					else if (eleRoll == 9)
						pinkShirt++;
					else if (eleRoll == 10)
						pinkLegs++;
					else if (eleRoll == 11)
						pinkBlouse++;
					else if (eleRoll == 12)
						pinkSkirt++;
					else if (eleRoll == 13)
						goldShirt++;
					else if (eleRoll == 14)
						goldBlouse++;
					else if (eleRoll == 15)
						goldLegs++;
					else if (eleRoll == 16)
						goldSkirt++;
				}
				}
			}
		}
		int masterRoll = rand() % 30 + 1;
		if (masterRoll == 1)
			masterCount++;
		counter++;
	}
	if (option == 1)
	{
		std::cout << "Total ranger boots: " << rangerBoots << '\n';
		std::cout << "Total wizzy boots: " << wizBoots << '\n';
		std::cout << "Total holy sandals: " << holySandals << '\n';
		std::cout << "Total spiked manacles: " << spikedManacles << '\n';
		std::cout << "Total climbing boots g: " << climbingBoot << '\n';
		std::cout << "Total medium clues done: " << ceil(counter / 4) << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = counter;
	returnCounters.return2 = rangerBoots;
	returnCounters.return3 = masterCount;
	return returnCounters;
}

clueBox eliteClue(int option)
{
	double counter = 0;
	int nature = 0, crystal = 0, lavaMask = 0, battlestaff = 0, antifire = 0, restore = 0, brew = 0, range = 0, gildScim = 0, gildBoots = 0, gildCoif = 0, gildVambs = 0, gildHideBody = 0,
		gildChaps = 0, gildPick = 0, gildAxe = 0, gildSpade = 0, gildFull = 0, gildPlate = 0, gildLegs = 0, gildSkirt = 0, gildKite = 0, gildMed = 0, gildChain = 0, gildSq = 0, gild2H = 0,
		gildSpear = 0, gildHastsa = 0, thirdHelm = 0, thirdPlate = 0, thirdLegs = 0, thirdSkirt = 0, thirdKite = 0, thirdCoif = 0, thirdRangeTop = 0, thirdRangeLegs = 0, thirdVambs = 0,
		thirdHat = 0, thirdRobeTop = 0, thirdRobeBottom = 0, thirdAmulet = 0, thirdSword = 0, thirdWand = 0, thirdCloak = 0, thirdBow = 0, tuxJacket = 0, tuxCuffs = 0, tuxTrousers = 0,
		tuxShoes = 0, tuxBowTie = 0, lightTuxJacket = 0, lightTuxCuffs = 0, lightTuxTrousers = 0, lightTuxShoes = 0, lightTuxBowTie = 0, thirdDruidicStaff = 0, thirdDruidicCloak = 0,
		thirdDruidicTop = 0, thirdDruidicLegs = 0, thirdPick = 0, thirdAxe = 0, mimicCount = 0, thirdAgeCount = 0;
	
	while (tuxJacket == 0 || tuxCuffs == 0 || tuxTrousers == 0 || tuxShoes == 0 || tuxBowTie == 0 || lightTuxJacket == 0 || lightTuxCuffs == 0 || lightTuxTrousers == 0 || lightTuxShoes == 0 ||
		lightTuxBowTie == 0 || nature == 0 || crystal == 0 || lavaMask == 0 /*||
		
		battlestaff == 0 || antifire == 0 || restore == 0 || brew == 0 || range == 0 || gildScim == 0 || gildBoots == 0 ||
		gildCoif == 0 || gildVambs == 0 || gildHideBody == 0 || gildChaps == 0 || gildPick == 0 || gildAxe == 0 || gildSpade == 0 || gildFull == 0 || gildPlate == 0 || gildLegs == 0 ||
		gildSkirt == 0 || gildKite == 0 || gildMed == 0 || gildChain == 0 || gildSq == 0 || gild2H == 0 ||
		gildSpear == 0 || gildHastsa == 0 || 
		
		thirdHelm == 0 || thirdPlate == 0 || thirdLegs == 0 || thirdSkirt == 0 || thirdKite == 0 || thirdCoif == 0 || thirdRangeTop == 0 || thirdRangeLegs == 0 || thirdVambs == 0 ||
		thirdHat == 0 || thirdRobeTop == 0 || thirdRobeBottom == 0 || thirdAmulet == 0 || thirdSword == 0 || thirdWand == 0 || thirdCloak == 0 || thirdBow == 0*/)
	{

		int mimicRoll = rand() % 35 + 1;
		if (mimicRoll == 35)
		{
			mimicCount++;
			int rareMimicRoll = rand() % 250 + 1;
			if (rareMimicRoll == 250)
			{
				thirdAgeCount++;
				int mimicThirdRoll = rand() % 23 + 1;
				if (mimicThirdRoll == 1)
					thirdCoif++;
				else if (mimicThirdRoll == 2)
					thirdRangeTop++;
				else if (mimicThirdRoll == 3)
					thirdRangeLegs++;
				else if (mimicThirdRoll == 4)
					thirdVambs++;
				else if (mimicThirdRoll == 5)
					thirdRobeTop++;
				else if (mimicThirdRoll == 6)
					thirdRobeBottom++;
				else if (mimicThirdRoll == 7)
					thirdHat++;
				else if (mimicThirdRoll == 8)
					thirdAmulet++;
				else if (mimicThirdRoll == 9)
					thirdLegs++;
				else if (mimicThirdRoll == 10)
					thirdPlate++;
				else if (mimicThirdRoll == 11)
					thirdHelm++;
				else if (mimicThirdRoll == 12)
					thirdSkirt++;
				else if (mimicThirdRoll == 13)
					thirdKite++;
				else if (mimicThirdRoll == 14)
					thirdSword++;
				else if (mimicThirdRoll == 15)
					thirdCloak++;
				else if (mimicThirdRoll == 16)
					thirdWand++;
				else if (mimicThirdRoll == 17)
					thirdBow++;
				else if (mimicThirdRoll == 18)
					thirdDruidicStaff++;
				else if (mimicThirdRoll == 19)
					thirdDruidicCloak++;
				else if (mimicThirdRoll == 20)
					thirdDruidicLegs++;
				else if (mimicThirdRoll == 21)
					thirdDruidicTop++;
				else if (mimicThirdRoll == 22)
					thirdPick++;
				else if (mimicThirdRoll == 23)
					thirdAxe++;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			int roll = rand() % 25 + 1;
			if (roll == 25)
			{
				int rareRoll = rand() % 50 + 1;
				if (rareRoll == 49)
				{
					int tuxRoll = rand() % 10 + 1;
					switch (tuxRoll)
					{
					case 1: tuxJacket++;
						break;
					case 2: tuxCuffs++;
						break;
					case 3: tuxTrousers++;
						break;
					case 4: tuxShoes++;
						break;
					case 5: tuxBowTie++;
						break;
					case 6: lightTuxJacket++;
						break;
					case 7: lightTuxCuffs++;
						break;
					case 8: lightTuxTrousers++;
						break;
					case 9: lightTuxShoes++;
						break;
					case 10: lightTuxBowTie++;
						break;
					}
				}
				else if (rareRoll == 50)
				{
					int megaRoll = rand() % 23 + 1;
					if (megaRoll == 1)
						nature++;
					else if (megaRoll == 2)
						crystal++;
					else if (megaRoll == 3)
						lavaMask++;
					else if (megaRoll == 4)
						battlestaff++;
					else if (megaRoll == 5)
						antifire++;
					else if (megaRoll == 6)
						restore++;
					else if (megaRoll == 7)
						brew++;
					else if (megaRoll == 8)
						range++;
					else if (megaRoll == 9)
						gildScim++;
					else if (megaRoll == 10)
						gildBoots++;
					else if (megaRoll == 11)
						gildCoif++;
					else if (megaRoll == 12)
						gildHideBody++;
					else if (megaRoll == 13)
						gildChaps++;
					else if (megaRoll == 14)
						gildPick++;
					else if (megaRoll == 15)
						gildAxe++;
					else if (megaRoll == 16)
						gildSpade++;
					else if (megaRoll > 16 && megaRoll < 22)
					{
						int gildRoll = rand() % 11 + 1;
						if (gildRoll == 1)
							gildPlate++;
						else if (gildRoll == 2)
							gildFull++;
						else if (gildRoll == 3)
							gildLegs++;
						else if (gildRoll == 4)
							gildSkirt++;
						else if (gildRoll == 5)
							gildKite++;
						else if (gildRoll == 6)
							gildMed++;
						else if (gildRoll == 7)
							gildChain++;
						else if (gildRoll == 8)
							gildSq++;
						else if (gildRoll == 9)
							gild2H++;
						else if (gildRoll == 10)
							gildSpear++;
						else if (gildRoll == 11)
							gildHastsa++;
					}
					else if (megaRoll == 22)
						gildVambs++;
					else if (megaRoll == 23)
					{
						thirdAgeCount++;
						int thirdRoll = rand() % 17 + 1;
						if (thirdRoll == 1)
							thirdCoif++;
						else if (thirdRoll == 2)
							thirdRangeTop++;
						else if (thirdRoll == 3)
							thirdRangeLegs++;
						else if (thirdRoll == 4)
							thirdVambs++;
						else if (thirdRoll == 5)
							thirdRobeTop++;
						else if (thirdRoll == 6)
							thirdRobeBottom++;
						else if (thirdRoll == 7)
							thirdHat++;
						else if (thirdRoll == 8)
							thirdAmulet++;
						else if (thirdRoll == 9)
							thirdPlate++;
						else if (thirdRoll == 10)
							thirdLegs++;
						else if (thirdRoll == 11)
							thirdHelm++;
						else if (thirdRoll == 12)
							thirdKite++;
						else if (thirdRoll == 13)
							thirdSkirt++;
						else if (thirdRoll == 14)
							thirdSword++;
						else if (thirdRoll == 15)
							thirdWand++;
						else if (thirdRoll == 16)
							thirdCloak++;
						else if (thirdRoll == 17)
							thirdBow++;
					}
				}
			}
		}
		counter++;
	}
	if (option == 1)
	{
		std::cout << "Total ring of natures: " << nature << '\n';
		std::cout << "Total lava dragon masks: " << lavaMask << '\n';
		std::cout << "Total gilded scimitars: " << gildScim << '\n';
		std::cout << "Total gilded boots: " << gildBoots << '\n';
		std::cout << "Total gilded platebodies: " << gildPlate << '\n';
		std::cout << "Total gilded platelegs: " << gildLegs << '\n';
		std::cout << "Total gilded full helms: " << gildFull << '\n';
		std::cout << "Total gilded kites: " << gildKite << '\n';
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total elite clues completed: " << counter << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = counter;
	returnCounters.return2 = thirdAgeCount;
	returnCounters.return3 = mimicCount;
	return returnCounters;
}

clueBox masterClue(int option, bool petOnly)
{
	double counter = 0;
	int occultO = 0, tortO = 0, anguishO = 0, tormentedO = 0, defO = 0, darkHood = 0, darkTop = 0, darkGloves = 0, darkBottom = 0, darkBoots = 0, samKasa = 0, samShirt = 0,
		samGloves = 0, samGreaves = 0, samBoots = 0, arcHood = 0, hosHood = 0, lovHood = 0, piscHood = 0, shayHood = 0, oldDemon = 0, lesserDemon = 0, greaterDemon = 0,
		blackDemon = 0, jungleDemon = 0, leftEye = 0, wig = 0, ale = 0, obsidian = 0, fancy = 0, halfMoon = 0, armadylO = 0, bandoO = 0, saraO = 0, zammyO = 0, dragonPlate = 0,
		ankouMask = 0, ankouTop = 0, ankouGloves = 0, ankouLegs = 0, ankouSocks = 0, mummyHead = 0, mummyBody = 0, mummyHands = 0, mummyLegs = 0, mummyFeet = 0, dragonKite = 0,
		thirdHelm = 0, thirdPlate = 0, thirdLegs = 0, thirdSkirt = 0, thirdKite = 0, thirdCoif = 0, thirdRangeTop = 0, thirdRangeLegs = 0, thirdVambs = 0,
		thirdHat = 0, thirdRobeTop = 0, thirdRobeBottom = 0, thirdAmulet = 0, thirdSword = 0, thirdWand = 0, thirdCloak = 0, thirdBow = 0, thirdDruidicStaff = 0, thirdDruidicCloak = 0,
		thirdDruidicTop = 0, thirdDruidicLegs = 0, thirdPick = 0, thirdAxe = 0, pet = 0, gildScim = 0, bucketG = 0, gildBoots = 0, ringCoins = 0, cabbage = 0, antiVenom = 0, torstol = 0,
		gildCoif = 0, gildVamb = 0, gildDTop = 0, gildChaps = 0, gildPick = 0, gildAxe = 0, gildSpade = 0, gildPlate = 0, gildLegs = 0, gildSkirt = 0, gildFullHelm = 0, gildKite = 0,
		gildMed = 0, gildChain = 0, gildSq = 0, gild2h = 0, gildSpear = 0, gildHasta = 0, mimicCount = 0, thirdAgeCount = 0;
	if (petOnly == 0)
	{
		while (occultO == 0 || tortO == 0 || anguishO == 0 || tormentedO == 0 || defO == 0 || darkHood == 0 || darkTop == 0 || darkGloves == 0 || darkBottom == 0 || darkBoots == 0 || samKasa == 0 || samShirt == 0 ||
			samGloves == 0 || samGreaves == 0 || samBoots == 0 || arcHood == 0 || hosHood == 0 || lovHood == 0 || piscHood == 0 || shayHood == 0 || oldDemon == 0 || lesserDemon == 0 || greaterDemon == 0 ||
			blackDemon == 0 || jungleDemon == 0 || leftEye == 0 || wig == 0 || ale == 0 || obsidian == 0 || fancy == 0 || halfMoon == 0 || armadylO == 0 || bandoO == 0 || saraO == 0 || zammyO == 0 || dragonPlate == 0 ||
			ankouMask == 0 || ankouTop == 0 || ankouGloves == 0 || ankouLegs == 0 || ankouSocks == 0 || mummyHead == 0 || mummyBody == 0 || mummyHands == 0 || mummyLegs == 0 || mummyFeet == 0 || dragonKite == 0


			/*|| thirdHelm == 0 || thirdPlate == 0 || thirdLegs == 0 || thirdSkirt == 0 || thirdKite == 0 || thirdCoif == 0 || thirdRangeTop == 0 || thirdRangeLegs == 0 || thirdVambs == 0 ||
			thirdHat == 0 || thirdRobeTop == 0 || thirdRobeBottom == 0 || thirdAmulet == 0 || thirdSword == 0 || thirdWand == 0 || thirdCloak == 0 || thirdBow == 0 || thirdDruidicStaff == 0 || thirdDruidicCloak == 0 ||
			thirdDruidicTop == 0 || thirdDruidicLegs == 0 || thirdPick == 0 || thirdAxe == 0*/)
		{
			for (int i = 0; i < 6; i++)
			{
				int roll = rand() % 23 + 1;
				if (roll == 23)
				{
					int rareRoll = rand() % 37 + 1;
					switch (rareRoll)
					{
					case 1: leftEye++;
						break;
					case 2: wig++;
						break;
					case 3: ale++;
						break;
					case 4: halfMoon++;
						break;
					case 5: fancy++;
						break;
					case 6: darkHood++;
						break;
					case 7: darkTop++;
						break;
					case 8: darkBottom++;
						break;
					case 9: darkBoots++;
						break;
					case 10: darkGloves++;
						break;
					case 11: obsidian++;
						break;
					case 12: occultO++;
						break;
					case 13: tortO++;
						break;
					case 14: defO++;
						break;
					case 15: samKasa++;
						break;
					case 16: samShirt++;
						break;
					case 17: samGreaves++;
						break;
					case 18: samBoots++;
						break;
					case 19: samGloves++;
						break;
					case 20: arcHood++;
						break;
					case 21: hosHood++;
						break;
					case 22: lovHood++;
						break;
					case 23: piscHood++;
						break;
					case 24: shayHood++;
						break;
					case 25: lesserDemon++;
						break;
					case 26: greaterDemon++;
						break;
					case 27: blackDemon++;
						break;
					case 28: jungleDemon++;
						break;
					case 29: oldDemon++;
						break;
					case 30: anguishO++;
						break;
					case 31: tormentedO++;
						break;
					case 32:
					{
						int megaRoll = rand() % 16 + 1;
						switch (megaRoll)
						{
						case 1: gildScim++;
							break;
						case 2: bucketG++;
							break;
						case 3: gildBoots++;
							break;
						case 4: ringCoins++;
							break;
						case 5: cabbage++;
							break;
						case 6: antiVenom++;
							break;
						case 7: torstol++;
							break;
						case 8: gildCoif++;
							break;
						case 9: gildVamb++;
							break;
						case 10: gildDTop++;
							break;
						case 11: gildChaps++;
							break;
						case 12: gildPick++;
							break;
						case 13: gildAxe++;
							break;
						case 14: gildSpade++;
							break;
						case 15:
						{
							int gildRoll = rand() % 11 + 1;
							switch (gildRoll)
							{
							case 1: gildPlate++;
								break;
							case 2: gildLegs++;
								break;
							case 3: gildSkirt++;
								break;
							case 4: gildFullHelm++;
								break;
							case 5: gildKite++;
								break;
							case 6: gildMed++;
								break;
							case 7: gildChain++;
								break;
							case 8: gildSq++;
								break;
							case 9: gild2h++;
								break;
							case 10: gildSpear++;
								break;
							case 11: gildHasta++;
								break;
							}
						}
							break;
						}
						if (megaRoll == 16) // 1-15 is gilded and other items, left out for now, shouldn't effect completion time
						{
							thirdAgeCount++;
							int thirdTable = rand() % 23 + 1;
							if (thirdTable == 1)
								thirdCoif++;
							else if (thirdTable == 2)
								thirdRangeTop++;
							else if (thirdTable == 3)
								thirdRangeLegs++;
							else if (thirdTable == 4)
								thirdVambs++;
							else if (thirdTable == 5)
								thirdRobeTop++;
							else if (thirdTable == 6)
								thirdRobeBottom++;
							else if (thirdTable == 7)
								thirdHat++;
							else if (thirdTable == 8)
								thirdAmulet++;
							else if (thirdTable == 9)
								thirdLegs++;
							else if (thirdTable == 10)
								thirdPlate++;
							else if (thirdTable == 11)
								thirdHelm++;
							else if (thirdTable == 12)
								thirdSkirt++;
							else if (thirdTable == 13)
								thirdKite++;
							else if (thirdTable == 14)
								thirdSword++;
							else if (thirdTable == 15)
								thirdCloak++;
							else if (thirdTable == 16)
								thirdWand++;
							else if (thirdTable == 17)
								thirdBow++;
							else if (thirdTable == 18)
								thirdDruidicStaff++;
							else if (thirdTable == 19)
								thirdDruidicCloak++;
							else if (thirdTable == 20)
								thirdDruidicLegs++;
							else if (thirdTable == 21)
								thirdDruidicTop++;
							else if (thirdTable == 22)
								thirdPick++;
							else if (thirdTable == 23)
								thirdAxe++;
						}
					}
					case 33:
						break;
					case 34:
					{
						int godRoll = rand() % 4 + 1;
						if (godRoll == 1)
							armadylO++;
						else if (godRoll == 2)
							bandoO++;
						else if (godRoll == 3)
							zammyO++;
						else if (godRoll == 4)
							saraO++;
					}
					break;
					case 35:
					{
						int ankouRoll = rand() % 5 + 1;
						if (ankouRoll == 1)
							ankouMask++;
						else if (ankouRoll == 2)
							ankouTop++;
						else if (ankouRoll == 3)
							ankouLegs++;
						else if (ankouRoll == 4)
							ankouGloves++;
						else if (ankouRoll == 5)
							ankouSocks++;
					}
					break;
					case 36:
					{
						int mummyRoll = rand() % 5 + 1;
						if (mummyRoll == 1)
							mummyHead++;
						else if (mummyRoll == 2)
							mummyBody++;
						else if (mummyRoll == 3)
							mummyLegs++;
						else if (mummyRoll == 4)
							mummyFeet++;
						else if (mummyRoll == 5)
							mummyHands++;
					}
					break;
					case 37:
					{
						int coinRoll = rand() % 10 + 1;
						if (coinRoll == 10)
						{
							int dragonRoll = rand() % 3 + 1;
							if (dragonRoll == 1)
								dragonKite++;
							else
								dragonPlate++;
						}
					}
					break;
					}
				}
			}
			int petRoll = rand() % 10 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 100 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int mimicRoll = rand() % 15 + 1;
			if (mimicRoll == 15)
			{
				mimicCount++;
				int rareMimicRoll = rand() % 228 + 1;
				if (rareMimicRoll == 228)
				{
					thirdAgeCount++;
					int mimicThirdRoll = rand() % 23 + 1;
					if (mimicThirdRoll == 1)
						thirdCoif++;
					else if (mimicThirdRoll == 2)
						thirdRangeTop++;
					else if (mimicThirdRoll == 3)
						thirdRangeLegs++;
					else if (mimicThirdRoll == 4)
						thirdVambs++;
					else if (mimicThirdRoll == 5)
						thirdRobeTop++;
					else if (mimicThirdRoll == 6)
						thirdRobeBottom++;
					else if (mimicThirdRoll == 7)
						thirdHat++;
					else if (mimicThirdRoll == 8)
						thirdAmulet++;
					else if (mimicThirdRoll == 9)
						thirdLegs++;
					else if (mimicThirdRoll == 10)
						thirdPlate++;
					else if (mimicThirdRoll == 11)
						thirdHelm++;
					else if (mimicThirdRoll == 12)
						thirdSkirt++;
					else if (mimicThirdRoll == 13)
						thirdKite++;
					else if (mimicThirdRoll == 14)
						thirdSword++;
					else if (mimicThirdRoll == 15)
						thirdCloak++;
					else if (mimicThirdRoll == 16)
						thirdWand++;
					else if (mimicThirdRoll == 17)
						thirdBow++;
					else if (mimicThirdRoll == 18)
						thirdDruidicStaff++;
					else if (mimicThirdRoll == 19)
						thirdDruidicCloak++;
					else if (mimicThirdRoll == 20)
						thirdDruidicLegs++;
					else if (mimicThirdRoll == 21)
						thirdDruidicTop++;
					else if (mimicThirdRoll == 22)
						thirdPick++;
					else if (mimicThirdRoll == 23)
						thirdAxe++;
				}
			}
			counter++;
		}
		if (option == 1)
		{
			std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
			std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
			std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
			std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
			std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
			std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
			std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
			std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
			std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
			std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
			std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
			std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
			std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
			std::cout << "Total 3rd age wands: " << thirdWand << '\n';
			std::cout << "Total 3rd age bows: " << thirdBow << '\n';
			std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
			std::cout << "Total 3rd age swords: " << thirdSword << '\n';
			std::cout << "Total 3rd age picks: " << thirdPick << '\n';
			std::cout << "Total 3rd age axe: " << thirdAxe << '\n';
			std::cout << "Total druidic tops: " << thirdDruidicTop << '\n';
			std::cout << "Total druidic legs: " << thirdDruidicLegs << '\n';
			std::cout << "Total druidic staff: " << thirdDruidicStaff << '\n';
			std::cout << "Total druidic cloaks: " << thirdDruidicCloak << '\n';
			std::cout << "Total master clues completed: " << counter << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = mimicCount;
		returnCounters.return3 = thirdAgeCount;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				int roll = rand() % 23 + 1;
				if (roll == 23)
				{
					int rareRoll = rand() % 37 + 1;
					switch (rareRoll)
					{
					case 1: leftEye++;
						break;
					case 2: wig++;
						break;
					case 3: ale++;
						break;
					case 4: halfMoon++;
						break;
					case 5: fancy++;
						break;
					case 6: darkHood++;
						break;
					case 7: darkTop++;
						break;
					case 8: darkBottom++;
						break;
					case 9: darkBoots++;
						break;
					case 10: darkGloves++;
						break;
					case 11: obsidian++;
						break;
					case 12: occultO++;
						break;
					case 13: tortO++;
						break;
					case 14: defO++;
						break;
					case 15: samKasa++;
						break;
					case 16: samShirt++;
						break;
					case 17: samGreaves++;
						break;
					case 18: samBoots++;
						break;
					case 19: samGloves++;
						break;
					case 20: arcHood++;
						break;
					case 21: hosHood++;
						break;
					case 22: lovHood++;
						break;
					case 23: piscHood++;
						break;
					case 24: shayHood++;
						break;
					case 25: lesserDemon++;
						break;
					case 26: greaterDemon++;
						break;
					case 27: blackDemon++;
						break;
					case 28: jungleDemon++;
						break;
					case 29: oldDemon++;
						break;
					case 30: anguishO++;
						break;
					case 31: tormentedO++;
						break;
					case 32:
					{
						int megaRoll = rand() % 16 + 1;
						switch (megaRoll)
						{
						case 1: gildScim++;
							break;
						case 2: bucketG++;
							break;
						case 3: gildBoots++;
							break;
						case 4: ringCoins++;
							break;
						case 5: cabbage++;
							break;
						case 6: antiVenom++;
							break;
						case 7: torstol++;
							break;
						case 8: gildCoif++;
							break;
						case 9: gildVamb++;
							break;
						case 10: gildDTop++;
							break;
						case 11: gildChaps++;
							break;
						case 12: gildPick++;
							break;
						case 13: gildAxe++;
							break;
						case 14: gildSpade++;
							break;
						case 15:
						{
							int gildRoll = rand() % 11 + 1;
							switch (gildRoll)
							{
							case 1: gildPlate++;
								break;
							case 2: gildLegs++;
								break;
							case 3: gildSkirt++;
								break;
							case 4: gildFullHelm++;
								break;
							case 5: gildKite++;
								break;
							case 6: gildMed++;
								break;
							case 7: gildChain++;
								break;
							case 8: gildSq++;
								break;
							case 9: gild2h++;
								break;
							case 10: gildSpear++;
								break;
							case 11: gildHasta++;
								break;
							}
						}
						break;
						}
						if (megaRoll == 16) // 1-15 is gilded and other items, left out for now, shouldn't effect completion time
						{
							thirdAgeCount++;
							int thirdTable = rand() % 23 + 1;
							if (thirdTable == 1)
								thirdCoif++;
							else if (thirdTable == 2)
								thirdRangeTop++;
							else if (thirdTable == 3)
								thirdRangeLegs++;
							else if (thirdTable == 4)
								thirdVambs++;
							else if (thirdTable == 5)
								thirdRobeTop++;
							else if (thirdTable == 6)
								thirdRobeBottom++;
							else if (thirdTable == 7)
								thirdHat++;
							else if (thirdTable == 8)
								thirdAmulet++;
							else if (thirdTable == 9)
								thirdLegs++;
							else if (thirdTable == 10)
								thirdPlate++;
							else if (thirdTable == 11)
								thirdHelm++;
							else if (thirdTable == 12)
								thirdSkirt++;
							else if (thirdTable == 13)
								thirdKite++;
							else if (thirdTable == 14)
								thirdSword++;
							else if (thirdTable == 15)
								thirdCloak++;
							else if (thirdTable == 16)
								thirdWand++;
							else if (thirdTable == 17)
								thirdBow++;
							else if (thirdTable == 18)
								thirdDruidicStaff++;
							else if (thirdTable == 19)
								thirdDruidicCloak++;
							else if (thirdTable == 20)
								thirdDruidicLegs++;
							else if (thirdTable == 21)
								thirdDruidicTop++;
							else if (thirdTable == 22)
								thirdPick++;
							else if (thirdTable == 23)
								thirdAxe++;
						}
					}
					case 33:
						break;
					case 34:
					{
						int godRoll = rand() % 4 + 1;
						if (godRoll == 1)
							armadylO++;
						else if (godRoll == 2)
							bandoO++;
						else if (godRoll == 3)
							zammyO++;
						else if (godRoll == 4)
							saraO++;
					}
					break;
					case 35:
					{
						int ankouRoll = rand() % 5 + 1;
						if (ankouRoll == 1)
							ankouMask++;
						else if (ankouRoll == 2)
							ankouTop++;
						else if (ankouRoll == 3)
							ankouLegs++;
						else if (ankouRoll == 4)
							ankouGloves++;
						else if (ankouRoll == 5)
							ankouSocks++;
					}
					break;
					case 36:
					{
						int mummyRoll = rand() % 5 + 1;
						if (mummyRoll == 1)
							mummyHead++;
						else if (mummyRoll == 2)
							mummyBody++;
						else if (mummyRoll == 3)
							mummyLegs++;
						else if (mummyRoll == 4)
							mummyFeet++;
						else if (mummyRoll == 5)
							mummyHands++;
					}
					break;
					case 37:
					{
						int coinRoll = rand() % 10 + 1;
						if (coinRoll < 10)
						{
							int dragonRoll = rand() % 3 + 1;
							if (dragonRoll == 1)
								dragonKite++;
							else
								dragonPlate++;
						}
					}
					break;
					}
				}
			}
			int petRoll = rand() % 10 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 100 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int mimicRoll = rand() % 15 + 1;
			if (mimicRoll == 15)
			{
				mimicCount++;
				int rareMimicRoll = rand() % 228 + 1;
				if (rareMimicRoll == 228)
				{
					thirdAgeCount++;
					int mimicThirdRoll = rand() % 23 + 1;
					if (mimicThirdRoll == 1)
						thirdCoif++;
					else if (mimicThirdRoll == 2)
						thirdRangeTop++;
					else if (mimicThirdRoll == 3)
						thirdRangeLegs++;
					else if (mimicThirdRoll == 4)
						thirdVambs++;
					else if (mimicThirdRoll == 5)
						thirdRobeTop++;
					else if (mimicThirdRoll == 6)
						thirdRobeBottom++;
					else if (mimicThirdRoll == 7)
						thirdHat++;
					else if (mimicThirdRoll == 8)
						thirdAmulet++;
					else if (mimicThirdRoll == 9)
						thirdLegs++;
					else if (mimicThirdRoll == 10)
						thirdPlate++;
					else if (mimicThirdRoll == 11)
						thirdHelm++;
					else if (mimicThirdRoll == 12)
						thirdSkirt++;
					else if (mimicThirdRoll == 13)
						thirdKite++;
					else if (mimicThirdRoll == 14)
						thirdSword++;
					else if (mimicThirdRoll == 15)
						thirdCloak++;
					else if (mimicThirdRoll == 16)
						thirdWand++;
					else if (mimicThirdRoll == 17)
						thirdBow++;
					else if (mimicThirdRoll == 18)
						thirdDruidicStaff++;
					else if (mimicThirdRoll == 19)
						thirdDruidicCloak++;
					else if (mimicThirdRoll == 20)
						thirdDruidicLegs++;
					else if (mimicThirdRoll == 21)
						thirdDruidicTop++;
					else if (mimicThirdRoll == 22)
						thirdPick++;
					else if (mimicThirdRoll == 23)
						thirdAxe++;
				}
			}
			counter++;
		}
		if (option == 1)
		{
			std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
			std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
			std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
			std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
			std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
			std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
			std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
			std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
			std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
			std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
			std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
			std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
			std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
			std::cout << "Total 3rd age wands: " << thirdWand << '\n';
			std::cout << "Total 3rd age bows: " << thirdBow << '\n';
			std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
			std::cout << "Total 3rd age swords: " << thirdSword << '\n';
			std::cout << "Total 3rd age picks: " << thirdPick << '\n';
			std::cout << "Total 3rd age axe: " << thirdAxe << '\n';
			std::cout << "Total druidic tops: " << thirdDruidicTop << '\n';
			std::cout << "Total druidic legs: " << thirdDruidicLegs << '\n';
			std::cout << "Total druidic staff: " << thirdDruidicStaff << '\n';
			std::cout << "Total druidic cloaks: " << thirdDruidicCloak << '\n';
			std::cout << "Total master clues completed: " << counter << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = counter;
		returnCounters.return2 = mimicCount;
		returnCounters.return3 = thirdAgeCount;
		return returnCounters;
	}
}

int fishingTrawler(int option)
{
	int hat = 0, top = 0, bottom = 0, boots = 0, counter = 0;
	while (hat == 0 || top == 0 || bottom == 0 || boots == 0)
	{
		int roll = rand() % 8 + 1;
		if (roll == 1)
		{
			int piece = rand() % 4 + 1;
			switch (piece)
			{
			case 1: hat++;
				break;
			case 2: top++;
				break;
			case 3: bottom++;
				break;
			case 4: boots++;
				break;
			}
		}
		counter++;
	}
	if (option == 1)
		std::cout << "Total games: " << counter << '\n';
	return counter;
}

clueBox alchemicalHydra(int option, bool petOnly)
{
	int dragonAxe = 0, dragonKnife = 0, hydraClaw = 0, hydraTail = 0, hydraLeather = 0, brimstoneRing = 0, pet = 0, killcount = 0, jar = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (dragonAxe == 0 || dragonKnife == 0 || hydraClaw == 0 || hydraTail == 0 || hydraLeather == 0 || brimstoneRing < 4 || pet == 0 || jar == 0)
		{
			int roll = 0, roll2 = 0, roll3 = 0, roll4 = 0, roll5 = 0, roll6 = 0, petRoll = 0;
			petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int jarRoll = rand() % 100 + 1;
			if (jarRoll == 1)
			{
				int jarRoll2 = rand() % 20 + 1;
				if (jarRoll2 == 1)
					jar++;
			}
			roll = rand() % 2000 + 1;
			if (roll == 1)
				dragonAxe++;
			if (roll != 1)
			{
				roll2 = rand() % 2000 + 1;
				if (roll2 == 1)
					dragonKnife++;
			}

			if (roll != 1 && roll2 != 1)
			{
				roll3 = rand() % 1000 + 1;
				if (roll3 == 1)
					hydraClaw++;
			}

			if (roll != 1 && roll2 != 1 && roll3 != 1)
			{
				roll4 = rand() % 512 + 1;
				if (roll4 == 1)
					hydraTail++;
			}

			if (roll != 1 && roll2 != 1 && roll3 != 1 && roll4 != 1)
			{
				roll5 = rand() % 512 + 1;
				if (roll5 == 1)
					hydraLeather++;
			}

			if (roll != 1 && roll2 != 1 && roll3 != 1 && roll4 != 1 && roll5 != 1)
			{
				roll6 = rand() % 180 + 1;
				if (roll6 == 1)
					brimstoneRing++;
			}

			killcount++;
			int clueRoll = rand() % 256;
			if (clueRoll == 1)
				clue++;
		}

		gp += VORKSTANDARD * killcount;
		gp += dragonAxe * DRAGONAXE;
		gp += dragonKnife * DRAGONKNIFE;
		gp += hydraClaw * HYDRACLAW;
		gp += hydraTail * HYDRATAIL;
		gp += hydraLeather * HYDRALEATHER;
		gp += brimstoneRing / 3 * BRIMSTONERING;

		if (option == 1)
		{
			std::cout << "You finished the Alchemical Hydra in " << killcount << " kills.\n";
			std::cout << "Dragon Throwaxes: " << dragonAxe << '\n';
			std::cout << "Dragon Knifes: " << dragonKnife << '\n';
			std::cout << "Hydra Claws: " << hydraClaw << '\n';
			std::cout << "Hydra Tails: " << hydraTail << '\n';
			std::cout << "Hydra Leathers: " << hydraLeather << '\n';
			std::cout << "Brimstone Ring Pieces: " << brimstoneRing << '\n';
			std::cout << "Ikkle Hydras: " << pet << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int roll = 0, roll2 = 0, roll3 = 0, roll4 = 0, roll5 = 0, roll6 = 0, petRoll = 0;
			petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int jarRoll = rand() % 100 + 1;
			if (jarRoll == 1)
			{
				int jarRoll2 = rand() % 20 + 1;
				if (jarRoll2 == 1)
					jar++;
			}
			roll = rand() % 2000 + 1;
			if (roll == 1)
				dragonAxe++;
			if (roll != 1)
			{
				roll2 = rand() % 2000 + 1;
				if (roll2 == 1)
					dragonKnife++;
			}

			if (roll != 1 && roll2 != 1)
			{
				roll3 = rand() % 1000 + 1;
				if (roll3 == 1)
					hydraClaw++;
			}

			if (roll != 1 && roll2 != 1 && roll3 != 1)
			{
				roll4 = rand() % 512 + 1;
				if (roll4 == 1)
					hydraTail++;
			}

			if (roll != 1 && roll2 != 1 && roll3 != 1 && roll4 != 1)
			{
				roll5 = rand() % 512 + 1;
				if (roll5 == 1)
					hydraLeather++;
			}

			if (roll != 1 && roll2 != 1 && roll3 != 1 && roll4 != 1 && roll5 != 1)
			{
				roll6 = rand() % 180 + 1;
				if (roll6 == 1)
					brimstoneRing++;
			}

			killcount++;
			int clueRoll = rand() % 256;
			if (clueRoll == 1)
				clue++;
		}

		gp += VORKSTANDARD * killcount;
		gp += dragonAxe * DRAGONAXE;
		gp += dragonKnife * DRAGONKNIFE;
		gp += hydraClaw * HYDRACLAW;
		gp += hydraTail * HYDRATAIL;
		gp += hydraLeather * HYDRALEATHER;
		gp += brimstoneRing / 3 * BRIMSTONERING;

		if (option == 1)
		{
			std::cout << "You finished the Alchemical Hydra in " << killcount << " kills.\n";
			std::cout << "Dragon Throwaxes: " << dragonAxe << '\n';
			std::cout << "Dragon Knifes: " << dragonKnife << '\n';
			std::cout << "Hydra Claws: " << hydraClaw << '\n';
			std::cout << "Hydra Tails: " << hydraTail << '\n';
			std::cout << "Hydra Leathers: " << hydraLeather << '\n';
			std::cout << "Brimstone Ring Pieces: " << brimstoneRing << '\n';
			std::cout << "Ikkle Hydras: " << pet << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox callisto(int option, bool petOnly)
{
	int killcount = 0, tyrannicalRing = 0, dragonPick = 0, dragon2h = 0, callistoCub = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (tyrannicalRing == 0 || dragonPick == 0 || dragon2h == 0 || callistoCub == 0)
		{
			int petRoll = rand() % 2000 + 1;
			if (petRoll == 1)
				callistoCub++;
			int roll = rand() % 256 + 1;
			if (roll < 4)
			{
				int roll2 = rand() % 6 + 1;
				if (roll2 == 1)
					tyrannicalRing++;
				else if (roll2 > 1 && roll2 < 4)
					dragon2h++;
				else if (roll2 > 3)
					dragonPick++;
			}
			killcount++;
			int clueRoll = rand() % 50;
			if (clueRoll == 1)
				clue++;
		}

		gp += tyrannicalRing * TYRANNICALRING;
		gp += DRAGONPICK * dragonPick;
		gp += killcount * CALLISTOSTANDARD;

		if (option == 1)
		{
			std::cout << "Total kills to complete Callist: " << killcount << '\n';
			std::cout << "Callisto Cubs: " << callistoCub << '\n';
			std::cout << "Tyrannical Rings: " << tyrannicalRing << '\n';
			std::cout << "Dragon 2hs: " << dragon2h << '\n';
			std::cout << "Dragon Pickaxes: " << dragonPick << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (callistoCub == 0)
		{
			int petRoll = rand() % 2000 + 1;
			if (petRoll == 1)
				callistoCub++;
			int roll = rand() % 256 + 1;
			if (roll < 4)
			{
				int roll2 = rand() % 6 + 1;
				if (roll2 == 1)
					tyrannicalRing++;
				else if (roll2 > 1 && roll2 < 4)
					dragon2h++;
				else if (roll2 > 3)
					dragonPick++;
			}
			killcount++;
			int clueRoll = rand() % 50;
			if (clueRoll == 1)
				clue++;
		}

		gp += tyrannicalRing * TYRANNICALRING;
		gp += DRAGONPICK * dragonPick;
		gp += killcount * CALLISTOSTANDARD;

		if (option == 1)
		{
			std::cout << "Total kills to complete Callist: " << killcount << '\n';
			std::cout << "Callisto Cubs: " << callistoCub << '\n';
			std::cout << "Tyrannical Rings: " << tyrannicalRing << '\n';
			std::cout << "Dragon 2hs: " << dragon2h << '\n';
			std::cout << "Dragon Pickaxes: " << dragonPick << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox cerberus(int option, bool petOnly)
{
	int hellPuppy = 0, prim = 0, peg = 0, etern = 0, smould = 0, jar = 0, killcount = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (hellPuppy == 0 || jar == 0 || prim == 0 || peg == 0 || etern == 0 || smould == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					hellPuppy++;
			}
			int jarRoll = rand() % 100 + 1;
			if (jarRoll == 1)
			{
				int jarRoll2 = rand() % 20 + 1;
				if (jarRoll2 == 1)
					jar++;
			}
			int roll = rand() % 128 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 4 + 1;
				switch (roll2)
				{
				case 1: prim++;
					break;
				case 2: peg++;
					break;
				case 3: etern++;
					break;
				case 4: smould++;
					break;
				}
			}
			killcount++;
			int clueRoll = rand() % 100;
			if (clueRoll == 1)
				clue++;
		}

		gp += CERBSTANDARD * killcount;
		gp += prim * PRIMORDIALCRYSTAL;
		gp += peg * PEGASIANCRYSTAL;
		gp += etern * ETERNALCRYSTAL;
		gp += smould * SMOULDERINGSTONE;

		if (option == 1)
		{
			std::cout << "You completed Cerberus in " << killcount << " kills.\n";
			std::cout << "Hellpuppies: " << hellPuppy << '\n';
			std::cout << "Primordial crystals: " << prim << '\n';
			std::cout << "Pegasian crystals: " << peg << '\n';
			std::cout << "Eternal crystals: " << etern << '\n';
			std::cout << "Smouldering crystals: " << smould << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (hellPuppy == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					hellPuppy++;
			}
			int jarRoll = rand() % 100 + 1;
			if (jarRoll == 1)
			{
				int jarRoll2 = rand() % 20 + 1;
				if (jarRoll2 == 1)
					jar++;
			}
			int roll = rand() % 128 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 4 + 1;
				switch (roll2)
				{
				case 1: prim++;
					break;
				case 2: peg++;
					break;
				case 3: etern++;
					break;
				case 4: smould++;
					break;
				}
			}
			killcount++;
			int clueRoll = rand() % 100;
			if (clueRoll == 1)
				clue++;
		}

		gp += CERBSTANDARD * killcount;
		gp += prim * PRIMORDIALCRYSTAL;
		gp += peg * PEGASIANCRYSTAL;
		gp += etern * ETERNALCRYSTAL;
		gp += smould * SMOULDERINGSTONE;

		if (option == 1)
		{
			std::cout << "You completed Cerberus in " << killcount << " kills.\n";
			std::cout << "Hellpuppies: " << hellPuppy << '\n';
			std::cout << "Primordial crystals: " << prim << '\n';
			std::cout << "Pegasian crystals: " << peg << '\n';
			std::cout << "Eternal crystals: " << etern << '\n';
			std::cout << "Smouldering crystals: " << smould << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox gauntlet(int option, bool petOnly)
{
	int crystalWep = 0, crystalArm = 0, blade = 0, youngllef = 0, killcount = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (crystalWep == 0 || crystalArm == 0 || blade == 0 || youngllef == 0)
		{
			int roll = rand() % 10 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 80 + 1;
				if (roll2 == 1)
					youngllef++;
				else if (roll2 > 1 && roll2 < 18)
					crystalWep++;
				else if (roll2 > 17 && roll2 < 34)
					crystalArm++;
				else if (roll2 > 33 && roll2 < 36)
					blade++;
			}
			killcount++;
			int clueRoll = rand() % 20;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * CORRUPTGAUNTSTANDARD;
		gp += blade * BLADESAELDOR;
		gp += CRYSTALWEP * crystalWep;
		gp += crystalArm * CRYSTALARMOR;

		if (option == 1)
		{
			std::cout << "Corrupted Gauntlet completions done to finish: " << killcount << '\n';
			std::cout << "Youngllefs: " << youngllef << '\n';
			std::cout << "Blade of Saeldors: " << blade << '\n';
			std::cout << "Crystal weapon seeds: " << crystalWep << '\n';
			std::cout << "Crystal armour seeds: " << crystalArm << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (youngllef == 0)
		{
			int roll = rand() % 10 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 80 + 1;
				if (roll2 == 1)
					youngllef++;
				else if (roll2 > 1 && roll2 < 18)
					crystalWep++;
				else if (roll2 > 17 && roll2 < 34)
					crystalArm++;
				else if (roll2 > 33 && roll2 < 36)
					blade++;
			}
			killcount++;
			int clueRoll = rand() % 20;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * CORRUPTGAUNTSTANDARD;
		gp += blade * BLADESAELDOR;
		gp += CRYSTALWEP * crystalWep;
		gp += crystalArm * CRYSTALARMOR;

		if (option == 1)
		{
			std::cout << "Corrupted Gauntlet completions done to finish: " << killcount << '\n';
			std::cout << "Youngllefs: " << youngllef << '\n';
			std::cout << "Blade of Saeldors: " << blade << '\n';
			std::cout << "Crystal weapon seeds: " << crystalWep << '\n';
			std::cout << "Crystal armour seeds: " << crystalArm << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

int chaosFanatic(int option, bool petOnly)
{
	int killcount = 0, odium = 0, malediction = 0, pet = 0;
	if (petOnly == 0)
	{
		while (odium == 0 || malediction == 0 || pet == 0)
		{
			int petRoll = rand() % 1000 + 1;
			if (petRoll == 1)
				pet++;
			int roll = rand() % 128 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 2 + 1;
				switch (roll2)
				{
				case 1: odium++;
					break;
				case 2: malediction++;
					break;
				}
			}
			killcount++;
		}
		if (option == 1)
		{
			std::cout << "Your killcount to complete fanatic was: " << killcount << '\n';
			std::cout << "Odium shards: " << odium << '\n';
			std::cout << "Malediction shards: " << malediction << '\n';
			std::cout << "Chaos Ele Pets: " << pet << '\n';
		}
		return killcount;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 1000 + 1;
			if (petRoll == 1)
				pet++;
			int roll = rand() % 128 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 2 + 1;
				switch (roll2)
				{
				case 1: odium++;
					break;
				case 2: malediction++;
					break;
				}
			}
			killcount++;
		}
		if (option == 1)
		{
			std::cout << "Your killcount to complete fanatic was: " << killcount << '\n';
			std::cout << "Odium shards: " << odium << '\n';
			std::cout << "Malediction shards: " << malediction << '\n';
			std::cout << "Chaos Ele Pets: " << pet << '\n';
		}
		return killcount;
	}
}

clueBox chaosEle(int option)
{
	int pet = 0, counter = 0, clue = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 300 + 1;
		if (roll == 1)
			pet++;
		counter++;
		int clueRoll = rand() % 100;
		if (clueRoll == 1)
			clue++;
	}

	gp += counter * CHAOSELESTANDARD;

	if (option == 1)
	{
		std::cout << "You finished chaos ele in " << counter << " chaos ele kills.\n";
		std::cout << "Total gp earned: " << gp << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = counter;
	returnCounters.return2 = gp;
	returnCounters.return3 = clue;
	return returnCounters;
}

clueBox zily(int option, bool petOnly)
{
	int killcount = 0, sword = 0, light = 0, cbow = 0, hilt = 0, pet = 0, shard1 = 0, shard2 = 0, shard3 = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (sword == 0 || light == 0 || cbow == 0 || hilt == 0 || pet == 0 || shard1 == 0 || shard2 == 0 || shard3 == 0)
		{
			for (int i = 0; i < 3; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 < 4)
						sword++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int roll = rand() % 127 + 1;
			if (roll == 1)
				sword++;
			else if (roll == 2)
			{
				int roll2 = rand() % 2 + 1;
				if (roll2 == 1)
					light++;
			}
			else if (roll == 3)
			{
				int roll2 = rand() % 4 + 1;
				if (roll2 == 1)
					cbow++;
				else if (roll2 == 2)
					hilt++;
			}
			else if (roll == 4)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			killcount++;
			int clueRoll = rand() % 250;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * ZILYSTANDARD;
		gp += sword * SARASWORD;
		gp += light * SARALIGHT;
		gp += cbow * ARMADYLCBOW;
		gp += hilt * SARAHILT;

		if (option == 1)
		{
			std::cout << "To completed Zilyana in " << killcount << " kills.\n";
			std::cout << "Pet Zilyanas: " << pet << '\n';
			std::cout << "Saraswords: " << sword << '\n';
			std::cout << "Sara lights: " << light << '\n';
			std::cout << "Armadyl Crossbows: " << cbow << '\n';
			std::cout << "Sara Hilts: " << hilt << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			for (int i = 0; i < 3; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 < 4)
						sword++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int roll = rand() % 127 + 1;
			if (roll == 1)
				sword++;
			else if (roll == 2)
			{
				int roll2 = rand() % 2 + 1;
				if (roll2 == 1)
					light++;
			}
			else if (roll == 3)
			{
				int roll2 = rand() % 4 + 1;
				if (roll2 == 1)
					cbow++;
				else if (roll2 == 2)
					hilt++;
			}
			else if (roll == 4)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			killcount++;
			int clueRoll = rand() % 250;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * ZILYSTANDARD;
		gp += sword * SARASWORD;
		gp += light * SARALIGHT;
		gp += cbow * ARMADYLCBOW;
		gp += hilt * SARAHILT;

		if (option == 1)
		{
			std::cout << "To completed Zilyana in " << killcount << " kills.\n";
			std::cout << "Pet Zilyanas: " << pet << '\n';
			std::cout << "Saraswords: " << sword << '\n';
			std::cout << "Sara lights: " << light << '\n';
			std::cout << "Armadyl Crossbows: " << cbow << '\n';
			std::cout << "Sara Hilts: " << hilt << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox jad(int option)
{
	int killcount = 0, pet = 0, cape = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 100 + 1;
		cape++;
		if (roll == 1)
			pet++;
		if (pet == 0)
		{
			int roll2 = rand() % 200 + 1;
			cape--;
			if (roll2 == 1)
				pet++;
		}
		killcount++;
	}

	gp += JADSTANDARD;

	if (option == 1)
	{
		std::cout << "You finished jad in " << killcount << " kills.\n";
		std::cout << "Total firecapes left: " << cape << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = killcount;
	returnCounters.return2 = gp;
	return returnCounters;
}

clueBox graardor(int option, bool petOnly)
{
	int killcount = 0, tassy = 0, chest = 0, boots = 0, hilt = 0, pet = 0, shard1 = 0, shard2 = 0, shard3 = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (tassy == 0 || chest == 0 || boots == 0 || hilt == 0/* || pet == 0 */|| shard1 == 0 || shard2 == 0 || shard3 == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			for (int i = 0; i < 3; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 == 1)
						tassy++;
					else if (minionRoll2 == 2)
						chest++;
					else if (minionRoll2 == 3)
						boots++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}
			int roll = rand() % 127 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 3 + 1;
				switch (roll2)
				{
				case 1: tassy++;
					break;
				case 2: chest++;
					break;
				case 3: boots++;
					break;
				}
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 4 + 1;
				if (roll2 == 1)
					hilt++;
			}
			else if (roll == 3)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			killcount++;
			int clueRoll = rand() % 250;
			if (clueRoll == 1)
				clue++;
		}

		gp += hilt * BANDOSHILT;
		gp += tassy * BANDOSTASSY;
		gp += chest * BANDOSCHEST;
		gp += boots * BANDOSBOOTS;
		gp += killcount * BANDOSSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished graardor in " << killcount << " kills.\n";
			std::cout << "Pet Graardors: " << pet << '\n';
			std::cout << "Bandos Hilts: " << hilt << '\n';
			std::cout << "Bandos Tassys: " << tassy << '\n';
			std::cout << "Bandos Chestplate: " << chest << '\n';
			std::cout << "Bandos Boots: " << boots << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			for (int i = 0; i < 3; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 == 1)
						tassy++;
					else if (minionRoll2 == 2)
						chest++;
					else if (minionRoll2 == 3)
						boots++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}
			int roll = rand() % 127 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 3 + 1;
				switch (roll2)
				{
				case 1: tassy++;
					break;
				case 2: chest++;
					break;
				case 3: boots++;
					break;
				}
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 4 + 1;
				if (roll2 == 1)
					hilt++;
			}
			else if (roll == 3)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			killcount++;
			int clueRoll = rand() % 250;
			if (clueRoll == 1)
				clue++;
		}

		gp += hilt * BANDOSHILT;
		gp += tassy * BANDOSTASSY;
		gp += chest * BANDOSCHEST;
		gp += boots * BANDOSBOOTS;
		gp += killcount * BANDOSSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished graardor in " << killcount << " kills.\n";
			std::cout << "Pet Graardors: " << pet << '\n';
			std::cout << "Bandos Hilts: " << hilt << '\n';
			std::cout << "Bandos Tassys: " << tassy << '\n';
			std::cout << "Bandos Chestplate: " << chest << '\n';
			std::cout << "Bandos Boots: " << boots << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox mole(int option)
{
	int pet = 0, killcount = 0, clue = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 100 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 30 + 1;
			if (roll2 == 1)
				pet++;
		}
		killcount++;
		int clueRoll = rand() % 500;
		if (clueRoll == 1)
			clue++;
	}

	gp += killcount * MOLESTANDARD;

	if (option == 1)
		std::cout << "You finished the Giant Mole in " << killcount << " kills.\n";
	clueBox returnCounters;
	returnCounters.return1 = killcount;
	returnCounters.return2 = gp;
	returnCounters.return3 = clue;
	return returnCounters;
}

clueBox grotGuardians(int option, bool petOnly)
{
	int killcount = 0, maul = 0, gloves = 0, ring = 0, hammer = 0, core = 0, pet = 0, jar = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (maul == 0 || gloves == 0 || ring == 0 || hammer == 0 || core == 0 || pet == 0 || jar == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			for (int i = 0; i < 2; i++)
			{
				int roll = rand() % 50 + 1;
				if (roll == 1 && i < 1)
				{
					int roll2 = rand() % 100 + 1;
					if (roll2 == 1)
						jar++;
				}
				else if (roll == 2)
				{
					int roll2 = rand() % 5 + 1;
					if (roll2 == 1)
						maul++;
				}
				else if (roll == 3)
				{
					int roll2 = rand() % 10 + 1;
					if (roll2 == 1)
						gloves++;
				}
				else if (roll == 4)
				{
					int roll2 = rand() % 10 + 1;
					if (roll2 == 1)
						ring++;
				}
				else if (roll == 5)
				{
					int roll2 = rand() % 15 + 1;
					if (roll2 == 1)
						hammer++;
				}
				else if (roll == 6)
				{
					int roll2 = rand() % 20 + 1;
					if (roll2 == 1)
						core++;
				}
			}
			killcount++;
			int clueRoll = rand() % 230;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * GROTGUARDSTANDARD;
		gp += hammer * GRANITEHAMMER;
		gp += core * TOURMALINECORE;

		if (option == 1)
		{
			std::cout << "You finished grotesque guardians in " << killcount << " kills.\n";
			std::cout << "Noon pets: " << pet << '\n';
			std::cout << "Jar of stones: " << jar << '\n';
			std::cout << "Granite mauls: " << maul << '\n';
			std::cout << "Granite gloves: " << gloves << '\n';
			std::cout << "Granite rings: " << ring << '\n';
			std::cout << "Granite hammers: " << hammer << '\n';
			std::cout << "Black tourmaline cores: " << core << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			for (int i = 0; i < 2; i++)
			{
				int roll = rand() % 50 + 1;
				if (roll == 1 && i < 1)
				{
					int roll2 = rand() % 100 + 1;
					if (roll2 == 1)
						jar++;
				}
				else if (roll == 2)
				{
					int roll2 = rand() % 5 + 1;
					if (roll2 == 1)
						maul++;
				}
				else if (roll == 3)
				{
					int roll2 = rand() % 10 + 1;
					if (roll2 == 1)
						gloves++;
				}
				else if (roll == 4)
				{
					int roll2 = rand() % 10 + 1;
					if (roll2 == 1)
						ring++;
				}
				else if (roll == 5)
				{
					int roll2 = rand() % 15 + 1;
					if (roll2 == 1)
						hammer++;
				}
				else if (roll == 6)
				{
					int roll2 = rand() % 20 + 1;
					if (roll2 == 1)
						core++;
				}
			}
			killcount++;
			int clueRoll = rand() % 230;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * GROTGUARDSTANDARD;
		gp += hammer * GRANITEHAMMER;
		gp += core * TOURMALINECORE;

		if (option == 1)
		{
			std::cout << "You finished grotesque guardians in " << killcount << " kills.\n";
			std::cout << "Noon pets: " << pet << '\n';
			std::cout << "Jar of stones: " << jar << '\n';
			std::cout << "Granite mauls: " << maul << '\n';
			std::cout << "Granite gloves: " << gloves << '\n';
			std::cout << "Granite rings: " << ring << '\n';
			std::cout << "Granite hammers: " << hammer << '\n';
			std::cout << "Black tourmaline cores: " << core << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox kalphiteQueen(int option, bool petOnly)
{
	int killcount = 0, chain = 0, sword = 0, pet = 0, jar = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (chain == 0 || sword == 0 || pet == 0 || jar == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int jarRoll = rand() % 100 + 1;
			if (jarRoll == 1)
			{
				int jarRoll2 = rand() % 20 + 1;
				if (jarRoll2 == 1)
					jar++;
			}

			int roll = rand() % 128 + 1;
			if (roll == 1)
				chain++;
			else if (roll == 2)
			{
				int roll2 = rand() % 2 + 1;
				if (roll2 == 1)
					sword++;
			}
			killcount++;
			int clueRoll = rand() % 100;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * KQSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished Kalphite Queen in " << killcount << " kills.\n";
			std::cout << "Kalphite Princesses: " << pet << '\n';
			std::cout << "Jars of sand: " << jar << '\n';
			std::cout << "Dragon Chainbodies: " << chain << '\n';
			std::cout << "Dragon 2h swords: " << sword << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int jarRoll = rand() % 100 + 1;
			if (jarRoll == 1)
			{
				int jarRoll2 = rand() % 20 + 1;
				if (jarRoll2 == 1)
					jar++;
			}

			int roll = rand() % 128 + 1;
			if (roll == 1)
				chain++;
			else if (roll == 2)
			{
				int roll2 = rand() % 2 + 1;
				if (roll2 == 1)
					sword++;
			}
			killcount++;
			int clueRoll = rand() % 100;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * KQSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished Kalphite Queen in " << killcount << " kills.\n";
			std::cout << "Kalphite Princesses: " << pet << '\n';
			std::cout << "Jars of sand: " << jar << '\n';
			std::cout << "Dragon Chainbodies: " << chain << '\n';
			std::cout << "Dragon 2h swords: " << sword << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox kbd(int option, bool petOnly)
{
	int killcount = 0, pet = 0, pick = 0, visage = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pet == 0 || visage == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int roll = rand() % 100 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 15 + 1;
				if (roll2 == 1)
					pick++;
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 50 + 1;
				if (roll2 == 1)
					visage++;
			}
			killcount++;
			int clueRoll = rand() % 450;
			if (clueRoll == 1)
				clue++;
		}

		gp += visage * DRACONICVISAGE;
		gp += pick * DRAGONPICK;
		gp += killcount * KBDSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished King Black Dragon in " << killcount << " kills.\n";
			std::cout << "Prince Black Dragon pets: " << pet << '\n';
			std::cout << "Dragon Pickaxes: " << pick << '\n';
			std::cout << "Draconic visages: " << visage << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int roll = rand() % 100 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 15 + 1;
				if (roll2 == 1)
					pick++;
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 50 + 1;
				if (roll2 == 1)
					visage++;
			}
			killcount++;
			int clueRoll = rand() % 450;
			if (clueRoll == 1)
				clue++;
		}

		gp += visage * DRACONICVISAGE;
		gp += pick * DRAGONPICK;
		gp += killcount * KBDSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished King Black Dragon in " << killcount << " kills.\n";
			std::cout << "Prince Black Dragon pets: " << pet << '\n';
			std::cout << "Dragon Pickaxes: " << pick << '\n';
			std::cout << "Draconic visages: " << visage << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox kraken(int option, bool petOnly)
{
	int killcount = 0, tent = 0, trident = 0, jar = 0, pet = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pet == 0 || jar == 0 || tent == 0 || trident == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int roll = rand() % 8 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 64 + 1;
				if (roll2 == 1)
					trident++;
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 50 + 1;
				if (roll2 == 1)
					tent++;
			}
			else if (roll == 3)
			{
				int roll2 = rand() % 125 + 1;
				if (roll2 == 1)
					jar++;
			}
			killcount++;
			int clueRoll = rand() % 500;
			if (clueRoll == 1)
				clue++;
		}

		gp += trident * TRIDENT;
		gp += tent * TENTACLE;
		gp += killcount * KRAKENSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished kraken in " << killcount << " kills.\n";
			std::cout << "Jars of swamp: " << jar << '\n';
			std::cout << "Pets: " << pet << '\n';
			std::cout << "Kraken Tentacles: " << tent << '\n';
			std::cout << "Tridents(full): " << trident << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int roll = rand() % 8 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 64 + 1;
				if (roll2 == 1)
					trident++;
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 50 + 1;
				if (roll2 == 1)
					tent++;
			}
			else if (roll == 3)
			{
				int roll2 = rand() % 125 + 1;
				if (roll2 == 1)
					jar++;
			}
			killcount++;
			int clueRoll = rand() % 500;
			if (clueRoll == 1)
				clue++;
		}

		gp += trident * TRIDENT;
		gp += tent * TENTACLE;
		gp += killcount * KRAKENSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished kraken in " << killcount << " kills.\n";
			std::cout << "Jars of swamp: " << jar << '\n';
			std::cout << "Pets: " << pet << '\n';
			std::cout << "Kraken Tentacles: " << tent << '\n';
			std::cout << "Tridents(full): " << trident << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox kril(int option, bool petOnly)
{
	int killcount = 0, steam = 0, spear = 0, staffDead = 0, hilt = 0, pet = 0, shard1 = 0, shard2 = 0, shard3 = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (steam == 0 || spear == 0 || staffDead == 0 || hilt == 0 || shard1 == 0 || shard2 == 0 || shard3 == 0 || pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			for (int i = 0; i < 3; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 == 1)
						spear++;
					else if (minionRoll2 == 2)
						spear++;
					else if (minionRoll2 == 3)
						spear++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}

			int roll = rand() % 127 + 1;
			if (roll == 1)
				spear++;
			else if (roll == 2)
				steam++;
			else if (roll == 3)
			{
				int roll2 = rand() % 4 + 1;
				if (roll2 == 1)
					staffDead++;
				else if (roll2 == 2)
					hilt++;
			}
			else if (roll == 4)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			killcount++;
			int clueRoll = rand() % 250;
			if (clueRoll == 1)
				clue++;
		}

		gp += spear * ZAMMYSPEAR;
		gp += steam * STEAMSTAFF;
		gp += hilt * ZAMMYHILT;
		gp += staffDead * STAFFOFDEAD;
		gp += killcount * ZAMMYSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished kril in " << killcount << " kills.\n";
			std::cout << "Zammy pets: " << pet << '\n';
			std::cout << "Zammy spears: " << spear << '\n';
			std::cout << "Steam battlestaves: " << steam << '\n';
			std::cout << "Zammy hilts: " << hilt << '\n';
			std::cout << "Staff of dead: " << staffDead << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 50 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			for (int i = 0; i < 3; i++) // minion kills
			{
				int minionRoll = rand() % 127 + 1;
				if (minionRoll == 1)
				{
					int minionRoll2 = rand() % 127 + 1;
					if (minionRoll2 == 1)
						spear++;
					else if (minionRoll2 == 2)
						spear++;
					else if (minionRoll2 == 3)
						spear++;
				}
				else if (minionRoll == 2)
				{
					int minionRoll2 = rand() % 12 + 1;
					if (minionRoll2 == 1)
						shard1++;
					else if (minionRoll2 == 2)
						shard2++;
					else if (minionRoll2 == 3)
						shard3++;
				}
			}

			int roll = rand() % 127 + 1;
			if (roll == 1)
				spear++;
			else if (roll == 2)
				steam++;
			else if (roll == 3)
			{
				int roll2 = rand() % 4 + 1;
				if (roll2 == 1)
					staffDead++;
				else if (roll2 == 2)
					hilt++;
			}
			else if (roll == 4)
			{
				int drop2 = rand() % 2 + 1;
				if (drop2 == 1)
				{
					int shardRoll = rand() % 3 + 1;
					switch (shardRoll)
					{
					case 1: shard1++;
						break;
					case 2: shard2++;
						break;
					case 3: shard3++;
						break;
					}
				}
			}
			killcount++;
			int clueRoll = rand() % 250;
			if (clueRoll == 1)
				clue++;
		}

		gp += spear * ZAMMYSPEAR;
		gp += steam * STEAMSTAFF;
		gp += hilt * ZAMMYHILT;
		gp += staffDead * STAFFOFDEAD;
		gp += killcount * ZAMMYSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished kril in " << killcount << " kills.\n";
			std::cout << "Zammy pets: " << pet << '\n';
			std::cout << "Zammy spears: " << spear << '\n';
			std::cout << "Steam battlestaves: " << steam << '\n';
			std::cout << "Zammy hilts: " << hilt << '\n';
			std::cout << "Staff of dead: " << staffDead << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox nightmare(int option, bool petOnly)
{ // assumes 5 man and equal damage distribution
	int killcount = 0, staff = 0, helm = 0, plate = 0, skirt = 0, mace = 0, eld = 0, harm = 0, vol = 0, jar = 0, pet = 0, seenStaff = 0, seenHelm = 0, seenPlate = 0, seenSkirt = 0,
		seenMace = 0, seenEld = 0, seenHarm = 0, seenVol = 0, seenJar = 0, seenPet = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (staff == 0 || helm == 0 || plate == 0 || skirt == 0 || mace == 0 || eld == 0 || harm == 0 || vol == 0 || jar == 0 || pet == 0)
		{
			int mvpRoll = rand() % 5 + 1;
			for (int i = 0; i < 5; i++)
			{
				if (mvpRoll == i)
				{
					int petRoll = rand() % 100 + 1;
					if (petRoll == 1)
					{
						int petRoll2 = rand() % 38 + 1;
						if (petRoll2 == 1)
						{
							if (i == 1)
								pet++;
							else
								seenPet++;
						}
					}
					int jarRoll = rand() % 100 + 1; // Was not able to find info if jar is a drop in addition to your loot drop, coded as if that is the case, can get a jar and still get loot
					if (jarRoll == 1)
					{
						int jarRoll2 = rand() % 19 + 1;
						if (jarRoll2 == 1)
						{
							if (i == 1)
								jar++;
							else
								seenJar++;
						}
					}
				}
				else
				{
					int petRoll = rand() % 100 + 1;
					if (petRoll == 1)
					{
						int petRoll2 = rand() % 40 + 1;
						if (petRoll2 == 1)
						{
							if (i == 1)
								pet++;
							else
								seenPet++;
						}
					}
					int jarRoll = rand() % 100 + 1;
					if (jarRoll == 1)
					{
						int jarRoll2 = rand() % 20 + 1;
						if (jarRoll2 == 1)
						{
							if (i == 1)
								jar++;
							else
								seenJar++;
						}
					}
				}
			}

			// rare table 1 (armor table)
			int table1Roll = rand() % 120 + 1;
			int table2Roll = rand() % 600 + 1;
			int player = rand() % 5 + 1;
			if (table1Roll == 1)
			{
				int table1Roll2 = rand() % 10 + 1;
				if (table1Roll2 == 1)
				{
					if (player == 1)
						mace++;
					else
						seenMace++;
				}
				else if (table1Roll2 > 1 && table1Roll2 < 4)
				{
					if (player == 1)
						helm++;
					else
						seenHelm++;
				}
				else if (table1Roll2 > 3 && table1Roll2 < 6)
				{
					if (player == 1)
						plate++;
					else
						seenPlate++;
				}
				else if (table1Roll2 > 5 && table1Roll2 < 8)
				{
					if (player == 1)
						skirt++;
					else
						seenSkirt++;
				}
				else if (table1Roll2 > 7)
				{
					if (player == 1)
						staff++;
					else
						seenStaff++;
				}
			}
			if (table2Roll == 1)
			{
				int table2Roll2 = rand() % 3 + 1;
				if (table2Roll2 == 1)
				{
					if (player == 1)
						eld++;
					else
						seenEld++;
				}
				else if (table2Roll2 == 2)
				{
					if (player == 1)
						harm++;
					else
						seenHarm++;
				}
				else if (table2Roll2 == 3)
				{
					if (player == 1)
						vol++;
					else
						seenVol++;
				}
			}
			killcount++;
			if (player == 1)
			{
				int clueRoll = rand() % 190;
				if (clueRoll == 1)
					clue++;
			}
			else
			{
				int clueRoll = rand() % 200;
				if (clueRoll == 1)
					clue++;
			}
		}

		gp += killcount * NIGHTMARESTANDARD;
		gp += ((helm + seenHelm) * INQHELM) / 5;
		gp += ((plate + seenPlate) * INQPLATE) / 5;
		gp += ((skirt + seenSkirt) * INQLEGS) / 5;
		gp += ((mace + seenMace) * INQMACE) / 5;
		gp += ((staff + seenStaff) * NIGHTMARESTAFF) / 5;
		gp += ((eld + seenEld) * ELDORB) / 5;
		gp += ((vol + seenVol) * VOLORB) / 5;
		gp += ((harm + seenHarm) * HARMORB) / 5;

		if (option == 1)
		{
			std::cout << "You finished the nightmare in " << killcount << '\n';
			std::cout << "Pets you got: " << pet << ". Pets you SAW: " << seenPet << '\n';
			std::cout << "Jars you got: " << jar << ". Jars you SAW: " << seenJar << '\n';
			std::cout << "Inq Helms you got: " << helm << ". Inq Helms you SAW: " << seenHelm << '\n';
			std::cout << "Inq Hauberks you got: " << plate << ". Inq Hauberks you SAW: " << seenPlate << '\n';
			std::cout << "Inq Skirts you got: " << skirt << ". Inq Skirts you SAW: " << seenSkirt << '\n';
			std::cout << "Inq Maces you got: " << mace << ". Inq Maces you SAW: " << seenMace << '\n';
			std::cout << "Nightmare Staves you got: " << staff << ". Nightmare Staves you SAW: " << seenStaff << '\n';
			std::cout << "Eldrich Orbs you got: " << eld << ". Eldrich Orbs you SAW: " << seenEld << '\n';
			std::cout << "Volatile Orbs you got: " << vol << ". Volatile Orbs you SAW: " << seenVol << '\n';
			std::cout << "Harmonised Orbs you got: " << harm << ". Harmonised Orbs you SAW: " << seenHarm << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int mvpRoll = rand() % 5 + 1;
			for (int i = 0; i < 5; i++)
			{
				if (mvpRoll == i)
				{
					int petRoll = rand() % 100 + 1;
					if (petRoll == 1)
					{
						int petRoll2 = rand() % 38 + 1;
						if (petRoll2 == 1)
						{
							if (i == 1)
								pet++;
							else
								seenPet++;
						}
					}
					int jarRoll = rand() % 100 + 1; // Was not able to find info if jar is a drop in addition to your loot drop, coded as if that is the case, can get a jar and still get loot
					if (jarRoll == 1)
					{
						int jarRoll2 = rand() % 19 + 1;
						if (jarRoll2 == 1)
						{
							if (i == 1)
								jar++;
							else
								seenJar++;
						}
					}
				}
				else
				{
					int petRoll = rand() % 100 + 1;
					if (petRoll == 1)
					{
						int petRoll2 = rand() % 40 + 1;
						if (petRoll2 == 1)
						{
							if (i == 1)
								pet++;
							else
								seenPet++;
						}
					}
					int jarRoll = rand() % 100 + 1;
					if (jarRoll == 1)
					{
						int jarRoll2 = rand() % 20 + 1;
						if (jarRoll2 == 1)
						{
							if (i == 1)
								jar++;
							else
								seenJar++;
						}
					}
				}
			}

			// rare table 1 (armor table)
			int table1Roll = rand() % 120 + 1;
			int table2Roll = rand() % 600 + 1;
			int player = rand() % 5 + 1;
			if (table1Roll == 1)
			{
				int table1Roll2 = rand() % 10 + 1;
				if (table1Roll2 == 1)
				{
					if (player == 1)
						mace++;
					else
						seenMace++;
				}
				else if (table1Roll2 > 1 && table1Roll2 < 4)
				{
					if (player == 1)
						helm++;
					else
						seenHelm++;
				}
				else if (table1Roll2 > 3 && table1Roll2 < 6)
				{
					if (player == 1)
						plate++;
					else
						seenPlate++;
				}
				else if (table1Roll2 > 5 && table1Roll2 < 8)
				{
					if (player == 1)
						skirt++;
					else
						seenSkirt++;
				}
				else if (table1Roll2 > 7)
				{
					if (player == 1)
						staff++;
					else
						seenStaff++;
				}
			}
			if (table2Roll == 1)
			{
				int table2Roll2 = rand() % 3 + 1;
				if (table2Roll2 == 1)
				{
					if (player == 1)
						eld++;
					else
						seenEld++;
				}
				else if (table2Roll2 == 2)
				{
					if (player == 1)
						harm++;
					else
						seenHarm++;
				}
				else if (table2Roll2 == 3)
				{
					if (player == 1)
						vol++;
					else
						seenVol++;
				}
			}
			killcount++;
			if (player == 1)
			{
				int clueRoll = rand() % 190;
				if (clueRoll == 1)
					clue++;
			}
			else
			{
				int clueRoll = rand() % 200;
				if (clueRoll == 1)
					clue++;
			}
		}

		gp += killcount * NIGHTMARESTANDARD;
		gp += ((helm + seenHelm) * INQHELM) / 5;
		gp += ((plate + seenPlate) * INQPLATE) / 5;
		gp += ((skirt + seenSkirt) * INQLEGS) / 5;
		gp += ((mace + seenMace) * INQMACE) / 5;
		gp += ((staff + seenStaff) * NIGHTMARESTAFF) / 5;
		gp += ((eld + seenEld) * ELDORB) / 5;
		gp += ((vol + seenVol) * VOLORB) / 5;
		gp += ((harm + seenHarm) * HARMORB) / 5;

		if (option == 1)
		{
			std::cout << "You finished the nightmare in " << killcount << '\n';
			std::cout << "Pets you got: " << pet << ". Pets you SAW: " << seenPet << '\n';
			std::cout << "Jars you got: " << jar << ". Jars you SAW: " << seenJar << '\n';
			std::cout << "Inq Helms you got: " << helm << ". Inq Helms you SAW: " << seenHelm << '\n';
			std::cout << "Inq Hauberks you got: " << plate << ". Inq Hauberks you SAW: " << seenPlate << '\n';
			std::cout << "Inq Skirts you got: " << skirt << ". Inq Skirts you SAW: " << seenSkirt << '\n';
			std::cout << "Inq Maces you got: " << mace << ". Inq Maces you SAW: " << seenMace << '\n';
			std::cout << "Nightmare Staves you got: " << staff << ". Nightmare Staves you SAW: " << seenStaff << '\n';
			std::cout << "Eldrich Orbs you got: " << eld << ". Eldrich Orbs you SAW: " << seenEld << '\n';
			std::cout << "Volatile Orbs you got: " << vol << ". Volatile Orbs you SAW: " << seenVol << '\n';
			std::cout << "Harmonised Orbs you got: " << harm << ". Harmonised Orbs you SAW: " << seenHarm << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox sarachnis(int option, bool petOnly)
{
	int killcount = 0, cudgel = 0, jar = 0, sraracha = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (cudgel == 0 || jar == 0 || sraracha == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					sraracha++;
			}

			int roll = rand() % 16 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 125 + 1;
				if (roll2 == 1)
					jar++;
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 24 + 1;
				if (roll2 == 1)
					cudgel++;
			}
			killcount++;
			int clueRoll = rand() % 60;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * SARACHNISSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished Sarachnis in " << killcount << " kills.\n";
			std::cout << "Sarachnis Cudgels: " << cudgel << '\n';
			std::cout << "Srarachas: " << sraracha << '\n';
			std::cout << "Jar of eyes: " << jar << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (sraracha == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					sraracha++;
			}

			int roll = rand() % 16 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 125 + 1;
				if (roll2 == 1)
					jar++;
			}
			else if (roll == 2)
			{
				int roll2 = rand() % 24 + 1;
				if (roll2 == 1)
					cudgel++;
			}
			killcount++;
			int clueRoll = rand() % 60;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * SARACHNISSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished Sarachnis in " << killcount << " kills.\n";
			std::cout << "Sarachnis Cudgels: " << cudgel << '\n';
			std::cout << "Srarachas: " << sraracha << '\n';
			std::cout << "Jar of eyes: " << jar << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox scorpia(int option, bool petOnly)
{
	int killcount = 0, malediction = 0, odium = 0, pet = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (malediction == 0 || odium == 0 || pet == 0)
		{
			int petRoll = rand() % 32 + 1; // wiki says drop rate is 1/2,016 as of making this, always was thought to be 1/2k, don't know where 2016 suddenly came from
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 63 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int roll = rand() % 128 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 2 + 1;
				if (roll2 == 1)
					malediction++;
				else if (roll2 == 2)
					odium++;
			}
			killcount++;
		}

		gp += killcount * SCORPIASTANDARD;

		if (option == 1)
		{
			std::cout << "You finished scorpia in " << killcount << " kills.\n";
			std::cout << "Scorpia offspring: " << pet << '\n';
			std::cout << "Malediction Shards: " << malediction << '\n';
			std::cout << "Odium Shards: " << odium << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 32 + 1; // wiki says drop rate is 1/2,016 as of making this, always was thought to be 1/2k, don't know where 2016 suddenly came from
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 63 + 1;
				if (petRoll2 == 1)
					pet++;
			}
			int roll = rand() % 128 + 1;
			if (roll == 1)
			{
				int roll2 = rand() % 2 + 1;
				if (roll2 == 1)
					malediction++;
				else if (roll2 == 2)
					odium++;
			}
			killcount++;
		}

		gp += killcount * SCORPIASTANDARD;

		if (option == 1)
		{
			std::cout << "You finished scorpia in " << killcount << " kills.\n";
			std::cout << "Scorpia offspring: " << pet << '\n';
			std::cout << "Malediction Shards: " << malediction << '\n';
			std::cout << "Odium Shards: " << odium << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		return returnCounters;
	}
}

clueBox skotizo(int option, bool petOnly)
{
	int killcount = 0, jar = 0, skotos = 0, claw = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (skotos == 0 || claw == 0 || jar == 0)
		{
			int petRoll = rand() % 65 + 1;
			if (petRoll == 1)
				skotos++;

			int roll = rand() % 25 + 1;
			if (roll == 1)
				claw++;
			else if (roll == 2)
			{
				int roll2 = rand() % 100 + 1;
				if (roll2 == 1)
					jar++;
			}
			killcount++;
			int clueRoll = rand() % 5;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * SKOTIZOSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished skotizo in " << killcount << " kills.\n";
			std::cout << "Jars of darkness: " << jar << '\n';
			std::cout << "Dark Claws: " << claw << '\n';
			std::cout << "Skotos pets: " << skotos << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (skotos == 0)
		{
			int petRoll = rand() % 65 + 1;
			if (petRoll == 1)
				skotos++;

			int roll = rand() % 25 + 1;
			if (roll == 1)
				claw++;
			else if (roll == 2)
			{
				int roll2 = rand() % 100 + 1;
				if (roll2 == 1)
					jar++;
			}
			killcount++;
			int clueRoll = rand() % 5;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * SKOTIZOSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished skotizo in " << killcount << " kills.\n";
			std::cout << "Jars of darkness: " << jar << '\n';
			std::cout << "Dark Claws: " << claw << '\n';
			std::cout << "Skotos pets: " << skotos << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox thermy(int option, bool petOnly)
{
	int killcount = 0, occult = 0, staff = 0, chain = 0, pet = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (occult == 0 || staff == 0 || chain == 0 || pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int roll = rand() % 350 + 1;
			if (roll == 1)
				occult++;
			else
			{
				roll = rand() % 16 + 1;
				if (roll == 1)
				{
					int roll2 = rand() % 32 + 1;
					if (roll2 == 1)
						staff++;
				}
				else if (roll == 2)
				{
					int roll2 = rand() % 125 + 1;
					if (roll2 == 1)
						chain++;
				}
			}
			killcount++;
			int clueRoll = rand() % 500;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * THERMYSTANDARD;
		gp += chain * DRAGONCHAIN;
		gp += occult * OCCULTNECKLACE;
		gp += staff * SMOKESTAFF;

		if (option == 1)
		{
			std::cout << "You finished thermy in " << killcount << " kills.\n";
			std::cout << "Thermy Pets: " << pet << '\n';
			std::cout << "Dragon Chain: " << chain << '\n';
			std::cout << "Occult necklace: " << occult << '\n';
			std::cout << "Smoke Battlestaves: " << staff << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 100 + 1;
			if (petRoll == 1)
			{
				int petRoll2 = rand() % 30 + 1;
				if (petRoll2 == 1)
					pet++;
			}

			int roll = rand() % 350 + 1;
			if (roll == 1)
				occult++;
			else
			{
				roll = rand() % 16 + 1;
				if (roll == 1)
				{
					int roll2 = rand() % 32 + 1;
					if (roll2 == 1)
						staff++;
				}
				else if (roll == 2)
				{
					int roll2 = rand() % 125 + 1;
					if (roll2 == 1)
						chain++;
				}
			}
			killcount++;
			int clueRoll = rand() % 500;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * THERMYSTANDARD;
		gp += chain * DRAGONCHAIN;
		gp += occult * OCCULTNECKLACE;
		gp += staff * SMOKESTAFF;

		if (option == 1)
		{
			std::cout << "You finished thermy in " << killcount << " kills.\n";
			std::cout << "Thermy Pets: " << pet << '\n';
			std::cout << "Dragon Chain: " << chain << '\n';
			std::cout << "Occult necklace: " << occult << '\n';
			std::cout << "Smoke Battlestaves: " << staff << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox venenatis(int option, bool petOnly)
{
	int killcount = 0, pick = 0, sword = 0, treasonous = 0, pet = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pick == 0 || sword == 0 || treasonous == 0 || pet == 0)
		{
			int petRoll = rand() % 2000 + 1;
			if (petRoll == 1)
				pet++;
			int roll = rand() % 256 + 1;
			if (roll < 4)
			{
				int roll2 = rand() % 6 + 1;
				if (roll2 == 1)
					treasonous++;
				else if (roll2 > 1 && roll2 < 4)
					sword++;
				else if (roll2 > 3)
					pick++;
			}
			killcount++;
			int clueRoll = rand() % 50;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * VENENATISSTANDARD;
		gp += treasonous * TREASONOUSRING;
		gp += pick * DRAGONPICK;

		if (option == 1)
		{
			std::cout << "Total kills to complete Venenatis: " << killcount << '\n';
			std::cout << "Spiderlings: " << pet << '\n';
			std::cout << "Treasonous Rings: " << treasonous << '\n';
			std::cout << "Dragon 2hs: " << sword << '\n';
			std::cout << "Dragon Pickaxes: " << pick << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 2000 + 1;
			if (petRoll == 1)
				pet++;
			int roll = rand() % 256 + 1;
			if (roll < 4)
			{
				int roll2 = rand() % 6 + 1;
				if (roll2 == 1)
					treasonous++;
				else if (roll2 > 1 && roll2 < 4)
					sword++;
				else if (roll2 > 3)
					pick++;
			}
			killcount++;
			int clueRoll = rand() % 50;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * VENENATISSTANDARD;
		gp += treasonous * TREASONOUSRING;
		gp += pick * DRAGONPICK;

		if (option == 1)
		{
			std::cout << "Total kills to complete Venenatis: " << killcount << '\n';
			std::cout << "Spiderlings: " << pet << '\n';
			std::cout << "Treasonous Rings: " << treasonous << '\n';
			std::cout << "Dragon 2hs: " << sword << '\n';
			std::cout << "Dragon Pickaxes: " << pick << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox vetion(int option, bool petOnly)
{
	int killcount = 0, pick = 0, sword = 0, gods = 0, pet = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (pick == 0 || sword == 0 || gods == 0 || pet == 0)
		{
			int petRoll = rand() % 2000 + 1;
			if (petRoll == 1)
				pet++;
			int roll = rand() % 256 + 1;
			if (roll < 4)
			{
				int roll2 = rand() % 6 + 1;
				if (roll2 == 1)
					gods++;
				else if (roll2 > 1 && roll2 < 4)
					sword++;
				else if (roll2 > 3)
					pick++;
			}
			killcount++;
			int clueRoll = rand() % 50;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * VETIONSTANDARD;
		gp += gods * RINGOFGODS;
		gp += pick * DRAGONPICK;

		if (option == 1)
		{
			std::cout << "Total kills to complete Vetion: " << killcount << '\n';
			std::cout << "Vet'ion jrs: " << pet << '\n';
			std::cout << "Ring of Gods: " << gods << '\n';
			std::cout << "Dragon 2hs: " << sword << '\n';
			std::cout << "Dragon Pickaxes: " << pick << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 2000 + 1;
			if (petRoll == 1)
				pet++;
			int roll = rand() % 256 + 1;
			if (roll < 4)
			{
				int roll2 = rand() % 6 + 1;
				if (roll2 == 1)
					gods++;
				else if (roll2 > 1 && roll2 < 4)
					sword++;
				else if (roll2 > 3)
					pick++;
			}
			killcount++;
			int clueRoll = rand() % 50;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * VETIONSTANDARD;
		gp += gods * RINGOFGODS;
		gp += pick * DRAGONPICK;

		if (option == 1)
		{
			std::cout << "Total kills to complete Vetion: " << killcount << '\n';
			std::cout << "Vet'ion jrs: " << pet << '\n';
			std::cout << "Ring of Gods: " << gods << '\n';
			std::cout << "Dragon 2hs: " << sword << '\n';
			std::cout << "Dragon Pickaxes: " << pick << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox zalcano(int option, bool petOnly)
{
	int killcount = 0, tool = 0, shard = 0, pet = 0, onyx = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (tool == 0 || shard == 0 || pet == 0)
		{
			int petRoll = rand() % 2250 + 1;
			if (petRoll == 1)
				pet++;

			int roll = rand() % 200 + 1;
			if (roll == 1)
			{
				int playerRoll = rand() % 5 + 1;
				if (playerRoll == 1)
					tool++;
			}
			else if (roll == 2) // Shard rate changes depending on contribution[1/750 to 1/1,500], went with 1/1k. Estimated with team of 4 each doing 250 of 1k damage, 250/400 max potential ~1/1030
			{
				int roll2 = rand() % 5 + 1;
				if (roll2 == 1)
					shard++;
			}
			else if (roll == 3)
			{
				int roll2 = rand() % 40 + 1;
				if (roll2 == 1)
				{
					int playerRoll = rand() % 5 + 1;
					if (playerRoll == 1)
						onyx++;
				}
			}
			killcount++;
		}

		gp += killcount * ZALCANOSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished Zalcano in " << killcount << " kills.\n";
			std::cout << "Zalcano Shards: " << shard << '\n';
			std::cout << "Smolcanos: " << pet << '\n';
			std::cout << "Crystal Tool Seeds: " << tool << '\n';
			std::cout << "Onyx: " << onyx << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			int petRoll = rand() % 2250 + 1;
			if (petRoll == 1)
				pet++;

			int roll = rand() % 200 + 1;
			if (roll == 1)
			{
				int playerRoll = rand() % 5 + 1;
				if (playerRoll == 1)
					tool++;
			}
			else if (roll == 2) // Shard rate changes depending on contribution[1/750 to 1/1,500], went with 1/1k. Estimated with team of 4 each doing 250 of 1k damage, 250/400 max potential ~1/1030
			{
				int roll2 = rand() % 5 + 1;
				if (roll2 == 1)
					shard++;
			}
			else if (roll == 3)
			{
				int roll2 = rand() % 40 + 1;
				if (roll2 == 1)
				{
					int playerRoll = rand() % 5 + 1;
					if (playerRoll == 1)
						onyx++;
				}
			}
			killcount++;
		}
		gp += killcount * ZALCANOSTANDARD;

		if (option == 1)
		{
			std::cout << "You finished Zalcano in " << killcount << " kills.\n";
			std::cout << "Zalcano Shards: " << shard << '\n';
			std::cout << "Smolcanos: " << pet << '\n';
			std::cout << "Crystal Tool Seeds: " << tool << '\n';
			std::cout << "Onyx: " << onyx << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		return returnCounters;
	}
}

thirdAgeBox efficientThirdAge(int option)
{
	// Clue table reference: https://docs.google.com/spreadsheets/d/16pVNHdZyynmxIbM9mynRDYT0LQsWxq-vbDs4_7DpnGM/edit#gid=2000272069
	// mmic table reference: https://twitter.com/JagexAsh/status/1158655373378805760
	// MASTER CLUES
	// MASTER CLUES
	// MASTER CLUES
	// MASTER CLUES Best for "easy" gilded and best for 3rd age
	// MASTER CLUES Do masters until master uniques are done, then elites until elite uniques are done, then hard until hard uniques done, then return to masters until finished
	double masterCounter = 0, extraMasterCount = 0;

	int superEnergy = 0, superRestore = 0, superSet = 0, gildedFullHelm = 0,

		robin = 0, plateT = 0, platelegsT = 0, kiteT = 0, fullHelmT = 0, plateG = 0, platelegsG = 0, kiteG = 0, fullHelmG = 0, plateZammy = 0, platelegsZammy = 0, kiteZammy = 0,
		fullHelmZammy = 0, plateSara = 0, platelegsSara = 0, kiteSara = 0, fullHelmSara = 0, plateGuthix = 0, platelegsGuthix = 0, kiteGuthix = 0, fullHelmGuthix = 0, tanCav = 0,
		darkCav = 0, blackCav = 0, pirateHat = 0, plateskirtG = 0, plateskirtT = 0, plateskirtZammy = 0, plateskirtSara = 0, plateskirtGuthix = 0, shieldH1 = 0, shieldH2 = 0, shieldH3 = 0,
		shieldH4 = 0, shieldH5 = 0, blueBodyG = 0, blueBodyT = 0, blueChapsG = 0, blueChapsT = 0, enchantedHat = 0, enchantedTop = 0, enchantedLegs = 0, helm1 = 0, helm2 = 0, helm3 = 0,
		helm4 = 0, helm5 = 0, gloryT = 0, zammyBracers = 0, zammyDBody = 0, zammyChaps = 0, zammyCoif = 0, guthixBracers = 0, guthixDBody = 0, guthixChaps = 0, guthixCoif = 0, saraBracers = 0,
		saraDBody = 0, saraChaps = 0, saraCoif = 0, saraCrozier = 0, guthixCrozier = 0, zammyCrozier = 0, saraStole = 0, guthixStole = 0, zammyStole = 0, redBodyT = 0, redChapsT = 0,
		redBodyG = 0, redChapsG = 0, whiteCav = 0, redCav = 0, navyCav = 0, pithHelm = 0, explorerBackpack = 0, plateBandos = 0, platelegsBandos = 0, plateskirtBandos = 0, fullHelmBandos = 0,
		kiteBandos = 0, plateArmadyl = 0, platelegsArmadyl = 0, plateskirtArmadyl = 0, fullHelmArmadyl = 0, kiteArmadyl = 0, plateAncient = 0, platelegsAncient = 0, plateskirtAncient = 0,
		fullHelmAncient = 0, kiteAncient = 0, ancientBracers = 0, ancientDBody = 0, ancientChaps = 0, ancientCoif = 0, bandosBracers = 0, bandosDBody = 0, bandosChaps = 0,
		bandosCoifs = 0, armadylBracers = 0, armadylDBody = 0, armadylChaps = 0, armadylCoif = 0, greenMask = 0, blueMask = 0, redMask = 0, blackMask = 0, zombieHead = 0, nunchaku = 0,
		cyclopsHead = 0, ancientBoots = 0, bandosBoots = 0, guthixBoots = 0, armadylBoots = 0, saraBoots = 0, zammyBoots = 0, dragonBootsOrn = 0, dualSai = 0, thievingBag = 0,
		runeDefenderKit = 0, tzhaarKit = 0, berserkerKit = 0, runeCane = 0, guthixShield = 0, saraShield = 0, zammyShield = 0, ancientShield = 0, armadylShield = 0, bandosShield = 0,
		plateH1 = 0, plateH2 = 0, plateH3 = 0, plateH4 = 0, plateH5 = 0;

	int nature = 0, crystal = 0, lavaMask = 0, battlestaff = 0, antifire = 0, restore = 0, brew = 0, range = 0, tuxJacket = 0, tuxCuffs = 0, tuxTrousers = 0,
		tuxShoes = 0, tuxBowTie = 0, lightTuxJacket = 0, lightTuxCuffs = 0, lightTuxTrousers = 0, lightTuxShoes = 0, lightTuxBowTie = 0;

	int occultO = 0, tortO = 0, anguishO = 0, tormentedO = 0, defO = 0, darkHood = 0, darkTop = 0, darkGloves = 0, darkBottom = 0, darkBoots = 0, samKasa = 0, samShirt = 0,
		samGloves = 0, samGreaves = 0, samBoots = 0, arcHood = 0, hosHood = 0, lovHood = 0, piscHood = 0, shayHood = 0, oldDemon = 0, lesserDemon = 0, greaterDemon = 0,
		blackDemon = 0, jungleDemon = 0, leftEye = 0, wig = 0, ale = 0, obsidian = 0, fancy = 0, halfMoon = 0, armadylO = 0, bandoO = 0, saraO = 0, zammyO = 0, dragonPlate = 0,
		ankouMask = 0, ankouTop = 0, ankouGloves = 0, ankouLegs = 0, ankouSocks = 0, mummyHead = 0, mummyBody = 0, mummyHands = 0, mummyLegs = 0, mummyFeet = 0, dragonKite = 0,
		thirdHelm = 0, thirdPlate = 0, thirdLegs = 0, thirdSkirt = 0, thirdKite = 0, thirdCoif = 0, thirdRangeTop = 0, thirdRangeLegs = 0, thirdVambs = 0,
		thirdHat = 0, thirdRobeTop = 0, thirdRobeBottom = 0, thirdAmulet = 0, thirdSword = 0, thirdWand = 0, thirdCloak = 0, thirdBow = 0, thirdDruidicStaff = 0, thirdDruidicCloak = 0,
		thirdDruidicTop = 0, thirdDruidicLegs = 0, thirdPick = 0, thirdAxe = 0, pet = 0, gildScim = 0, bucketG = 0, gildBoots = 0, ringCoins = 0, cabbage = 0, antiVenom = 0, torstol = 0,
		gildCoif = 0, gildVamb = 0, gildDTop = 0, gildChaps = 0, gildPick = 0, gildAxe = 0, gildSpade = 0, gildPlate = 0, gildLegs = 0, gildSkirt = 0, gildFullHelm = 0, gildKite = 0,
		gildMed = 0, gildChain = 0, gildSq = 0, gild2h = 0, gildSpear = 0, gildHasta = 0, mimicCount = 0, thirdAgeCount = 0;

	while (occultO == 0 || tortO == 0 || anguishO == 0 || tormentedO == 0 || defO == 0 || darkHood == 0 || darkTop == 0 || darkGloves == 0 || darkBottom == 0 || darkBoots == 0 || samKasa == 0 ||
		samShirt == 0 || samGloves == 0 || samGreaves == 0 || samBoots == 0 || arcHood == 0 || hosHood == 0 || lovHood == 0 || piscHood == 0 || shayHood == 0 || oldDemon == 0 || lesserDemon == 0 ||
		greaterDemon == 0 || blackDemon == 0 || jungleDemon == 0 || leftEye == 0 || wig == 0 || ale == 0 || obsidian == 0 || fancy == 0 || halfMoon == 0 || armadylO == 0 || bandoO == 0 ||
		saraO == 0 || zammyO == 0 || dragonPlate == 0 || ankouMask == 0 || ankouTop == 0 || ankouGloves == 0 || ankouLegs == 0 || ankouSocks == 0 || mummyHead == 0 || mummyBody == 0 ||
		mummyHands == 0 || mummyLegs == 0 || mummyFeet == 0 || dragonKite == 0 || ringCoins == 0  || bucketG == 0 || pet == 0 || thirdDruidicStaff == 0 || thirdDruidicCloak == 0 ||
		thirdDruidicTop == 0 || thirdDruidicLegs == 0 || thirdPick == 0 || thirdAxe == 0 || thirdSword == 0 || thirdWand == 0 || thirdCloak == 0 || thirdBow == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			int roll = rand() % 23 + 1;
			if (roll == 23)
			{
				int rareRoll = rand() % 37 + 1;
				switch (rareRoll)
				{
				case 1: leftEye++;
					break;
				case 2: wig++;
					break;
				case 3: ale++;
					break;
				case 4: halfMoon++;
					break;
				case 5: fancy++;
					break;
				case 6: darkHood++;
					break;
				case 7: darkTop++;
					break;
				case 8: darkBottom++;
					break;
				case 9: darkBoots++;
					break;
				case 10: darkGloves++;
					break;
				case 11: obsidian++;
					break;
				case 12: occultO++;
					break;
				case 13: tortO++;
					break;
				case 14: defO++;
					break;
				case 15: samKasa++;
					break;
				case 16: samShirt++;
					break;
				case 17: samGreaves++;
					break;
				case 18: samBoots++;
					break;
				case 19: samGloves++;
					break;
				case 20: arcHood++;
					break;
				case 21: hosHood++;
					break;
				case 22: lovHood++;
					break;
				case 23: piscHood++;
					break;
				case 24: shayHood++;
					break;
				case 25: lesserDemon++;
					break;
				case 26: greaterDemon++;
					break;
				case 27: blackDemon++;
					break;
				case 28: jungleDemon++;
					break;
				case 29: oldDemon++;
					break;
				case 30: anguishO++;
					break;
				case 31: tormentedO++;
					break;
				case 32:
				{
					int megaRoll = rand() % 16 + 1;
					switch (megaRoll)
					{
					case 1: gildScim++;
						break;
					case 2: bucketG++;
						break;
					case 3: gildBoots++;
						break;
					case 4: ringCoins++;
						break;
					case 5: cabbage++;
						break;
					case 6: antiVenom++;
						break;
					case 7: torstol++;
						break;
					case 8: gildCoif++;
						break;
					case 9: gildVamb++;
						break;
					case 10: gildDTop++;
						break;
					case 11: gildChaps++;
						break;
					case 12: gildPick++;
						break;
					case 13: gildAxe++;
						break;
					case 14: gildSpade++;
						break;
					case 15:
					{
						int gildRoll = rand() % 11 + 1;
						switch (gildRoll)
						{
						case 1: gildPlate++;
							break;
						case 2: gildLegs++;
							break;
						case 3: gildSkirt++;
							break;
						case 4: gildFullHelm++;
							break;
						case 5: gildKite++;
							break;
						case 6: gildMed++;
							break;
						case 7: gildChain++;
							break;
						case 8: gildSq++;
							break;
						case 9: gild2h++;
							break;
						case 10: gildSpear++;
							break;
						case 11: gildHasta++;
							break;
						}
					}
					break;
					}
					if (megaRoll == 16)
					{
						int thirdTable = rand() % 23 + 1;
						if (thirdTable == 1)
							thirdCoif++;
						else if (thirdTable == 2)
							thirdRangeTop++;
						else if (thirdTable == 3)
							thirdRangeLegs++;
						else if (thirdTable == 4)
							thirdVambs++;
						else if (thirdTable == 5)
							thirdRobeTop++;
						else if (thirdTable == 6)
							thirdRobeBottom++;
						else if (thirdTable == 7)
							thirdHat++;
						else if (thirdTable == 8)
							thirdAmulet++;
						else if (thirdTable == 9)
							thirdLegs++;
						else if (thirdTable == 10)
							thirdPlate++;
						else if (thirdTable == 11)
							thirdHelm++;
						else if (thirdTable == 12)
							thirdSkirt++;
						else if (thirdTable == 13)
							thirdKite++;
						else if (thirdTable == 14)
							thirdSword++;
						else if (thirdTable == 15)
							thirdCloak++;
						else if (thirdTable == 16)
							thirdWand++;
						else if (thirdTable == 17)
							thirdBow++;
						else if (thirdTable == 18)
							thirdDruidicStaff++;
						else if (thirdTable == 19)
							thirdDruidicCloak++;
						else if (thirdTable == 20)
							thirdDruidicLegs++;
						else if (thirdTable == 21)
							thirdDruidicTop++;
						else if (thirdTable == 22)
							thirdPick++;
						else if (thirdTable == 23)
							thirdAxe++;
					}
				}
				case 33:
					break;
				case 34:
				{
					int godRoll = rand() % 4 + 1;
					if (godRoll == 1)
						armadylO++;
					else if (godRoll == 2)
						bandoO++;
					else if (godRoll == 3)
						zammyO++;
					else if (godRoll == 4)
						saraO++;
				}
				break;
				case 35:
				{
					int ankouRoll = rand() % 5 + 1;
					if (ankouRoll == 1)
						ankouMask++;
					else if (ankouRoll == 2)
						ankouTop++;
					else if (ankouRoll == 3)
						ankouLegs++;
					else if (ankouRoll == 4)
						ankouGloves++;
					else if (ankouRoll == 5)
						ankouSocks++;
				}
				break;
				case 36:
				{
					int mummyRoll = rand() % 5 + 1;
					if (mummyRoll == 1)
						mummyHead++;
					else if (mummyRoll == 2)
						mummyBody++;
					else if (mummyRoll == 3)
						mummyLegs++;
					else if (mummyRoll == 4)
						mummyFeet++;
					else if (mummyRoll == 5)
						mummyHands++;
				}
				break;
				case 37:
				{
					int coinRoll = rand() % 10 + 1;
					if (coinRoll < 10)
					{
						int dragonRoll = rand() % 3 + 1;
						if (dragonRoll == 1)
							dragonKite++;
						else
							dragonPlate++;
					}
				}
				break;
				}
			}
		}

		int mimicRoll = rand() % 15 + 1;
		if (mimicRoll == 15)
		{
			int rareMimicRoll = rand() % 228 + 1;
			if (rareMimicRoll == 228)
			{
				int mimicThirdRoll = rand() % 23 + 1;
				if (mimicThirdRoll == 1)
					thirdCoif++;
				else if (mimicThirdRoll == 2)
					thirdRangeTop++;
				else if (mimicThirdRoll == 3)
					thirdRangeLegs++;
				else if (mimicThirdRoll == 4)
					thirdVambs++;
				else if (mimicThirdRoll == 5)
					thirdRobeTop++;
				else if (mimicThirdRoll == 6)
					thirdRobeBottom++;
				else if (mimicThirdRoll == 7)
					thirdHat++;
				else if (mimicThirdRoll == 8)
					thirdAmulet++;
				else if (mimicThirdRoll == 9)
					thirdLegs++;
				else if (mimicThirdRoll == 10)
					thirdPlate++;
				else if (mimicThirdRoll == 11)
					thirdHelm++;
				else if (mimicThirdRoll == 12)
					thirdSkirt++;
				else if (mimicThirdRoll == 13)
					thirdKite++;
				else if (mimicThirdRoll == 14)
					thirdSword++;
				else if (mimicThirdRoll == 15)
					thirdCloak++;
				else if (mimicThirdRoll == 16)
					thirdWand++;
				else if (mimicThirdRoll == 17)
					thirdBow++;
				else if (mimicThirdRoll == 18)
					thirdDruidicStaff++;
				else if (mimicThirdRoll == 19)
					thirdDruidicCloak++;
				else if (mimicThirdRoll == 20)
					thirdDruidicLegs++;
				else if (mimicThirdRoll == 21)
					thirdDruidicTop++;
				else if (mimicThirdRoll == 22)
					thirdPick++;
				else if (mimicThirdRoll == 23)
					thirdAxe++;
			}
		}
		int petRoll = rand() % 1000 + 1;
		if (petRoll == 1)
			pet++;
		masterCounter++;
	}
	if (option == 1)
	{
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total 3rd age picks: " << thirdPick << '\n';
		std::cout << "Total 3rd age axe: " << thirdAxe << '\n';
		std::cout << "Total druidic tops: " << thirdDruidicTop << '\n';
		std::cout << "Total druidic legs: " << thirdDruidicLegs << '\n';
		std::cout << "Total druidic staff: " << thirdDruidicStaff << '\n';
		std::cout << "Total druidic cloaks: " << thirdDruidicCloak << '\n';
		std::cout << "Total master clues completed: " << masterCounter << '\n';
		std::cout << "First master cycle finished\n\n\n";
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ELITE CLUES
	// ELITE CLUES
	// ELITE CLUES
	// ELITE CLUES

	double eliteCounter = 0;

	while (nature == 0 || lavaMask == 0 || tuxJacket == 0 || tuxCuffs == 0 || tuxTrousers == 0 || tuxShoes == 0 || tuxBowTie == 0 || lightTuxJacket == 0 || lightTuxCuffs == 0 || lightTuxTrousers == 0 || lightTuxShoes == 0 ||
		lightTuxBowTie == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			int roll = rand() % 25 + 1;
			if (roll == 25)
			{
				int rareRoll = rand() % 50 + 1;
				if (rareRoll == 49)
				{
					int tuxRoll = rand() % 10 + 1;
					switch (tuxRoll)
					{
					case 1: tuxJacket++;
						break;
					case 2: tuxCuffs++;
						break;
					case 3: tuxTrousers++;
						break;
					case 4: tuxShoes++;
						break;
					case 5: tuxBowTie++;
						break;
					case 6: lightTuxJacket++;
						break;
					case 7: lightTuxCuffs++;
						break;
					case 8: lightTuxTrousers++;
						break;
					case 9: lightTuxShoes++;
						break;
					case 10: lightTuxBowTie++;
						break;
					}
				}
				if (rareRoll == 50)
				{
					int megaRoll = rand() % 23 + 1;
					if (megaRoll == 1)
						nature++;
					else if (megaRoll == 2)
						crystal++;
					else if (megaRoll == 3)
						lavaMask++;
					else if (megaRoll == 4)
						battlestaff++;
					else if (megaRoll == 5)
						antifire++;
					else if (megaRoll == 6)
						restore++;
					else if (megaRoll == 7)
						brew++;
					else if (megaRoll == 8)
						range++;
					else if (megaRoll == 9)
						gildScim++;
					else if (megaRoll == 10)
						gildBoots++;
					else if (megaRoll == 11)
						gildCoif++;
					else if (megaRoll == 12)
						gildDTop++;
					else if (megaRoll == 13)
						gildChaps++;
					else if (megaRoll == 14)
						gildPick++;
					else if (megaRoll == 15)
						gildAxe++;
					else if (megaRoll == 16)
						gildSpade++;
					else if (megaRoll > 16 && megaRoll < 22)
					{
						int gildRoll = rand() % 11 + 1;
						if (gildRoll == 1)
							gildPlate++;
						else if (gildRoll == 2)
							gildFullHelm++;
						else if (gildRoll == 3)
							gildLegs++;
						else if (gildRoll == 4)
							gildSkirt++;
						else if (gildRoll == 5)
							gildKite++;
						else if (gildRoll == 6)
							gildMed++;
						else if (gildRoll == 7)
							gildChain++;
						else if (gildRoll == 8)
							gildSq++;
						else if (gildRoll == 9)
							gild2h++;
						else if (gildRoll == 10)
							gildSpear++;
						else if (gildRoll == 11)
							gildHasta++;
					}
					else if (megaRoll == 22)
						gildVamb++;
					else if (megaRoll == 23)
					{
						int thirdRoll = rand() % 17 + 1;
						if (thirdRoll == 1)
							thirdCoif++;
						else if (thirdRoll == 2)
							thirdRangeTop++;
						else if (thirdRoll == 3)
							thirdRangeLegs++;
						else if (thirdRoll == 4)
							thirdVambs++;
						else if (thirdRoll == 5)
							thirdRobeTop++;
						else if (thirdRoll == 6)
							thirdRobeBottom++;
						else if (thirdRoll == 7)
							thirdHat++;
						else if (thirdRoll == 8)
							thirdAmulet++;
						else if (thirdRoll == 9)
							thirdPlate++;
						else if (thirdRoll == 10)
							thirdLegs++;
						else if (thirdRoll == 11)
							thirdHelm++;
						else if (thirdRoll == 12)
							thirdKite++;
						else if (thirdRoll == 13)
							thirdSkirt++;
						else if (thirdRoll == 14)
							thirdSword++;
						else if (thirdRoll == 15)
							thirdWand++;
						else if (thirdRoll == 16)
							thirdCloak++;
						else if (thirdRoll == 17)
							thirdBow++;
					}
				}
			}
		}
		int mimicRoll = rand() % 35 + 1;
		if (mimicRoll == 35)
		{
			int rareMimicRoll = rand() % 250 + 1;
			if (rareMimicRoll == 250)
			{
				int mimicThirdRoll = rand() % 23 + 1;
				if (mimicThirdRoll == 1)
					thirdCoif++;
				else if (mimicThirdRoll == 2)
					thirdRangeTop++;
				else if (mimicThirdRoll == 3)
					thirdRangeLegs++;
				else if (mimicThirdRoll == 4)
					thirdVambs++;
				else if (mimicThirdRoll == 5)
					thirdRobeTop++;
				else if (mimicThirdRoll == 6)
					thirdRobeBottom++;
				else if (mimicThirdRoll == 7)
					thirdHat++;
				else if (mimicThirdRoll == 8)
					thirdAmulet++;
				else if (mimicThirdRoll == 9)
					thirdLegs++;
				else if (mimicThirdRoll == 10)
					thirdPlate++;
				else if (mimicThirdRoll == 11)
					thirdHelm++;
				else if (mimicThirdRoll == 12)
					thirdSkirt++;
				else if (mimicThirdRoll == 13)
					thirdKite++;
				else if (mimicThirdRoll == 14)
					thirdSword++;
				else if (mimicThirdRoll == 15)
					thirdCloak++;
				else if (mimicThirdRoll == 16)
					thirdWand++;
				else if (mimicThirdRoll == 17)
					thirdBow++;
				else if (mimicThirdRoll == 18)
					thirdDruidicStaff++;
				else if (mimicThirdRoll == 19)
					thirdDruidicCloak++;
				else if (mimicThirdRoll == 20)
					thirdDruidicLegs++;
				else if (mimicThirdRoll == 21)
					thirdDruidicTop++;
				else if (mimicThirdRoll == 22)
					thirdPick++;
				else if (mimicThirdRoll == 23)
					thirdAxe++;
			}
		}
		int master = rand() % 5 + 1;
		if (master == 1)
			extraMasterCount++;
		eliteCounter++;
	}
	if (option == 1)
	{
		std::cout << "Total ring of natures: " << nature << '\n';
		std::cout << "Total lava dragon masks: " << lavaMask << '\n';
		std::cout << "Total dark tux jackets: " << tuxJacket << '\n';
		std::cout << "Total dark tux trousers: " << tuxTrousers << '\n';
		std::cout << "Total light tux jackets: " << lightTuxJacket << '\n';
		std::cout << "Total light tux trousers: " << lightTuxTrousers << '\n';
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total elite clues completed: " << eliteCounter << '\n';
		std::cout << "First elite cycle finished\n\n\n";
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HARD CLUES
// HARD CLUES
// HARD CLUES
// HARD CLUES
//random 4-6 rolls
// 1/15 for master
// 1/13 for rare
// 1/1625 for mega rare(1/125 on rare table)
	double hardCounter = 0;

	while (guthixShield == 0 || saraShield == 0 || zammyShield == 0 || ancientShield == 0 || armadylShield == 0 || bandosShield == 0 || plateH1 == 0 || plateH2 == 0 ||
		plateH3 == 0 || plateH4 == 0 || plateH5 == 0 || thirdPlate == 0 || thirdHelm == 0 || thirdLegs == 0 || thirdSkirt == 0 || thirdKite == 0 || thirdAmulet == 0 ||
		thirdRobeBottom == 0 || thirdRobeBottom == 0 || thirdHat == 0 || thirdRangeLegs == 0 || thirdRangeTop == 0 || thirdCoif == 0 || thirdVambs == 0)
	{
		int hardRolls = rand() % 3 + 4;
		for (int i = 0; i < hardRolls; i++)
		{
			int initialTable = rand() % 13 + 1;
			if (initialTable == 1) // hit rare table
			{
				int rareTable = rand() % 125 + 1;
				if (rareTable == 2)
				{
					int shieldRoll = rand() % 6 + 1;
					switch (shieldRoll)
					{
					case 1: guthixShield++;
						break;
					case 2: saraShield++;
						break;
					case 3: zammyShield++;
						break;
					case 4: ancientShield++;
						break;
					case 5: armadylShield++;
						break;
					case 6: bandosShield++;
						break;
					}
				}
				else if (rareTable == 3)
				{
					int heraldicRoll = rand() % 5 + 1;
					switch (heraldicRoll)
					{
					case 1: plateH1++;
						break;
					case 2: plateH2++;
						break;
					case 3: plateH3++;
						break;
					case 4: plateH4++;
						break;
					case 5: plateH5++;
						break;
					}
				}
				else if (rareTable == 1) // hit mega rare table
				{
					int megaRareTable = rand() % 10 + 1;
					if (megaRareTable == 1)
						superEnergy += 15;
					else if (megaRareTable == 2)
						restore += 15;
					else if (megaRareTable == 3)
						antifire += 15;
					else if (megaRareTable == 4)
						superSet += 15;
					else if (megaRareTable == 5)
					{
						int thirdAgeRoll = rand() % 13 + 1;
						if (thirdAgeRoll == 1)
							thirdHelm++;
						else if (thirdAgeRoll == 2)
							thirdPlate++;
						else if (thirdAgeRoll == 3)
							thirdLegs++;
						else if (thirdAgeRoll == 4)
							thirdSkirt++;
						else if (thirdAgeRoll == 5)
							thirdKite++;
						else if (thirdAgeRoll == 6)
							thirdCoif++;
						else if (thirdAgeRoll == 7)
							thirdRangeTop++;
						else if (thirdAgeRoll == 8)
							thirdRangeLegs++;
						else if (thirdAgeRoll == 9)
							thirdVambs++;
						else if (thirdAgeRoll == 10)
							thirdHat++;
						else if (thirdAgeRoll == 11)
							thirdRobeTop++;
						else if (thirdAgeRoll == 12)
							thirdRobeBottom++;
						else if (thirdAgeRoll == 13)
							thirdAmulet++;
					}
					else if (5 < megaRareTable < 11)
					{
						int gildRoll = rand() % 11 + 1;
						if (gildRoll == 1)
							gildFullHelm++;
						else if (gildRoll == 2)
							gildPlate++;
						else if (gildRoll == 3)
							gildLegs++;
						else if (gildRoll == 4)
							gildSkirt++;
						else if (gildRoll == 5)
							gildKite++;
						else if (gildRoll == 6)
							gildMed++;
						else if (gildRoll == 7)
							gildChain++;
						else if (gildRoll == 8)
							gildSq++;
						else if (gildRoll == 9)
							gild2h++;
						else if (gildRoll == 10)
							gildSpear++;
						else if (gildRoll == 11)
							gildHasta++;
					}
				}
			}
		}
		int master = rand() % 15 + 1;
		if (master == 1)
			extraMasterCount++;
		hardCounter++;
	}
	if (option == 1)
	{
		std::cout << "Total hard clues completed: " << hardCounter << '\n';
		std::cout << "Total masters: " << extraMasterCount << '\n';
		std::cout << "3rd Age Platebodies: " << thirdPlate << '\n';
		std::cout << "3rd Age Platelegs: " << thirdLegs << '\n';
		std::cout << "3rd Age Full Helms: " << thirdHelm << '\n';
		std::cout << "3rd Age KiteShields: " << thirdKite << '\n';
		std::cout << "3rd Age Plateskirts: " << thirdSkirt << '\n';
		std::cout << "3rd Age Robetop: " << thirdRobeTop << '\n';
		std::cout << "3rd Age Robebottom: " << thirdRobeBottom << '\n';
		std::cout << "3rd Age Mage Hat: " << thirdHat << '\n';
		std::cout << "3rd Age Amulet: " << thirdAmulet << '\n';
		std::cout << "3rd Age Coif: " << thirdCoif << '\n';
		std::cout << "3rd Age Range Top: " << thirdRangeTop << '\n';
		std::cout << "3rd Age Range Legs: " << thirdRangeLegs << '\n';
		std::cout << "3rd Age Vambs: " << thirdVambs << '\n';
		std::cout << "Super Sets: " << superSet << '\n';
		std::cout << "Super energies: " << superEnergy << '\n';
		std::cout << "Super restores: " << restore << '\n';
		std::cout << "Antifires: " << antifire << '\n';
		std::cout << "Gilded Platebodies: " << gildPlate << '\n';
		std::cout << "Gilded Platelegs: " << gildLegs << '\n';
		std::cout << "Gilded full helm: " << gildFullHelm << '\n';
		std::cout << "Gilded kiteshield: " << gildKite << '\n';
		std::cout << "Gilded plateskirt: " << gildSkirt << '\n';
		std::cout << "Gilded med helm: " << gildMed << '\n';
		std::cout << "Gilded chainbody: " << gildChain << '\n';
		std::cout << "Gilded square shield: " << gildSq << '\n';
		std::cout << "Gilded 2h: " << gild2h << '\n';
		std::cout << "Gilded spear: " << gildSpear << '\n';
		std::cout << "Gilded hasta: " << gildHasta << '\n';
		std::cout << "Bandos shield: " << bandosShield << '\n';
		std::cout << "Arma shield: " << armadylShield << '\n';
		std::cout << "Ancient shield: " << ancientShield << '\n';
		std::cout << "Zammy shield: " << zammyShield << '\n';
		std::cout << "Sara shield: " << saraShield << '\n';
		std::cout << "Guthix shield: " << guthixShield << '\n';
		std::cout << "First hard cycle finished\n\n\n";
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MASTER CLUES
// MASTER CLUES
// MASTER CLUES
// MASTER CLUES Best for "easy" gilded and best for 3rd age
	/*
	while (thirdHelm == 0 || thirdPlate == 0 || thirdLegs == 0 || thirdSkirt == 0 || thirdKite == 0 || thirdCoif == 0 || thirdRangeTop == 0 || thirdRangeLegs == 0 || thirdVambs == 0 ||
		thirdHat == 0 || thirdRobeTop == 0 || thirdRobeBottom == 0 || thirdAmulet == 0 || thirdSword == 0 || thirdWand == 0 || thirdCloak == 0 || thirdBow == 0)
	{
		for (int i = 0; i < 6; i++)
		{
			int roll = rand() % 23 + 1;
			if (roll == 23)
			{
				int rareRoll = rand() % 37 + 1;
				switch (rareRoll)
				{
				case 1: leftEye++;
					break;
				case 2: wig++;
					break;
				case 3: ale++;
					break;
				case 4: halfMoon++;
					break;
				case 5: fancy++;
					break;
				case 6: darkHood++;
					break;
				case 7: darkTop++;
					break;
				case 8: darkBottom++;
					break;
				case 9: darkBoots++;
					break;
				case 10: darkGloves++;
					break;
				case 11: obsidian++;
					break;
				case 12: occultO++;
					break;
				case 13: tortO++;
					break;
				case 14: defO++;
					break;
				case 15: samKasa++;
					break;
				case 16: samShirt++;
					break;
				case 17: samGreaves++;
					break;
				case 18: samBoots++;
					break;
				case 19: samGloves++;
					break;
				case 20: arcHood++;
					break;
				case 21: hosHood++;
					break;
				case 22: lovHood++;
					break;
				case 23: piscHood++;
					break;
				case 24: shayHood++;
					break;
				case 25: lesserDemon++;
					break;
				case 26: greaterDemon++;
					break;
				case 27: blackDemon++;
					break;
				case 28: jungleDemon++;
					break;
				case 29: oldDemon++;
					break;
				case 30: anguishO++;
					break;
				case 31: tormentedO++;
					break;
				case 32:
				{
					int megaRoll = rand() % 16 + 1;
					switch (megaRoll)
					{
					case 1: gildScim++;
						break;
					case 2: bucketG++;
						break;
					case 3: gildBoots++;
						break;
					case 4: ringCoins++;
						break;
					case 5: cabbage++;
						break;
					case 6: antiVenom++;
						break;
					case 7: torstol++;
						break;
					case 8: gildCoif++;
						break;
					case 9: gildVamb++;
						break;
					case 10: gildDTop++;
						break;
					case 11: gildChaps++;
						break;
					case 12: gildPick++;
						break;
					case 13: gildAxe++;
						break;
					case 14: gildSpade++;
						break;
					case 15:
					{
						int gildRoll = rand() % 11 + 1;
						switch (gildRoll)
						{
						case 1: gildPlate++;
							break;
						case 2: gildLegs++;
							break;
						case 3: gildSkirt++;
							break;
						case 4: gildFullHelm++;
							break;
						case 5: gildKite++;
							break;
						case 6: gildMed++;
							break;
						case 7: gildChain++;
							break;
						case 8: gildSq++;
							break;
						case 9: gild2h++;
							break;
						case 10: gildSpear++;
							break;
						case 11: gildHasta++;
							break;
						}
					}
					break;
					}
					if (megaRoll == 16)
					{
						int thirdTable = rand() % 23 + 1;
						if (thirdTable == 1)
							thirdCoif++;
						else if (thirdTable == 2)
							thirdRangeTop++;
						else if (thirdTable == 3)
							thirdRangeLegs++;
						else if (thirdTable == 4)
							thirdVambs++;
						else if (thirdTable == 5)
							thirdRobeTop++;
						else if (thirdTable == 6)
							thirdRobeBottom++;
						else if (thirdTable == 7)
							thirdHat++;
						else if (thirdTable == 8)
							thirdAmulet++;
						else if (thirdTable == 9)
							thirdLegs++;
						else if (thirdTable == 10)
							thirdPlate++;
						else if (thirdTable == 11)
							thirdHelm++;
						else if (thirdTable == 12)
							thirdSkirt++;
						else if (thirdTable == 13)
							thirdKite++;
						else if (thirdTable == 14)
							thirdSword++;
						else if (thirdTable == 15)
							thirdCloak++;
						else if (thirdTable == 16)
							thirdWand++;
						else if (thirdTable == 17)
							thirdBow++;
						else if (thirdTable == 18)
							thirdDruidicStaff++;
						else if (thirdTable == 19)
							thirdDruidicCloak++;
						else if (thirdTable == 20)
							thirdDruidicLegs++;
						else if (thirdTable == 21)
							thirdDruidicTop++;
						else if (thirdTable == 22)
							thirdPick++;
						else if (thirdTable == 23)
							thirdAxe++;
					}
				}
				case 33:
					break;
				case 34:
				{
					int godRoll = rand() % 4 + 1;
					if (godRoll == 1)
						armadylO++;
					else if (godRoll == 2)
						bandoO++;
					else if (godRoll == 3)
						zammyO++;
					else if (godRoll == 4)
						saraO++;
				}
				break;
				case 35:
				{
					int ankouRoll = rand() % 5 + 1;
					if (ankouRoll == 1)
						ankouMask++;
					else if (ankouRoll == 2)
						ankouTop++;
					else if (ankouRoll == 3)
						ankouLegs++;
					else if (ankouRoll == 4)
						ankouGloves++;
					else if (ankouRoll == 5)
						ankouSocks++;
				}
				break;
				case 36:
				{
					int mummyRoll = rand() % 5 + 1;
					if (mummyRoll == 1)
						mummyHead++;
					else if (mummyRoll == 2)
						mummyBody++;
					else if (mummyRoll == 3)
						mummyLegs++;
					else if (mummyRoll == 4)
						mummyFeet++;
					else if (mummyRoll == 5)
						mummyHands++;
				}
				break;
				case 37:
				{
					int coinRoll = rand() % 10 + 1;
					if (coinRoll < 10)
					{
						int dragonRoll = rand() % 3 + 1;
						if (dragonRoll == 1)
							dragonKite++;
						else
							dragonPlate++;
					}
				}
				break;
				}
			}
		}

		int mimicRoll = rand() % 15 + 1;
		if (mimicRoll == 15)
		{
			int rareMimicRoll = rand() % 228 + 1;
			if (rareMimicRoll == 228)
			{
				int mimicThirdRoll = rand() % 23 + 1;
				if (mimicThirdRoll == 1)
					thirdCoif++;
				else if (mimicThirdRoll == 2)
					thirdRangeTop++;
				else if (mimicThirdRoll == 3)
					thirdRangeLegs++;
				else if (mimicThirdRoll == 4)
					thirdVambs++;
				else if (mimicThirdRoll == 5)
					thirdRobeTop++;
				else if (mimicThirdRoll == 6)
					thirdRobeBottom++;
				else if (mimicThirdRoll == 7)
					thirdHat++;
				else if (mimicThirdRoll == 8)
					thirdAmulet++;
				else if (mimicThirdRoll == 9)
					thirdLegs++;
				else if (mimicThirdRoll == 10)
					thirdPlate++;
				else if (mimicThirdRoll == 11)
					thirdHelm++;
				else if (mimicThirdRoll == 12)
					thirdSkirt++;
				else if (mimicThirdRoll == 13)
					thirdKite++;
				else if (mimicThirdRoll == 14)
					thirdSword++;
				else if (mimicThirdRoll == 15)
					thirdCloak++;
				else if (mimicThirdRoll == 16)
					thirdWand++;
				else if (mimicThirdRoll == 17)
					thirdBow++;
				else if (mimicThirdRoll == 18)
					thirdDruidicStaff++;
				else if (mimicThirdRoll == 19)
					thirdDruidicCloak++;
				else if (mimicThirdRoll == 20)
					thirdDruidicLegs++;
				else if (mimicThirdRoll == 21)
					thirdDruidicTop++;
				else if (mimicThirdRoll == 22)
					thirdPick++;
				else if (mimicThirdRoll == 23)
					thirdAxe++;
			}
		}
		masterCounter++;
	}
	if (option == 1)
	{
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total 3rd age picks: " << thirdPick << '\n';
		std::cout << "Total 3rd age axe: " << thirdAxe << '\n';
		std::cout << "Total druidic tops: " << thirdDruidicTop << '\n';
		std::cout << "Total druidic legs: " << thirdDruidicLegs << '\n';
		std::cout << "Total druidic staff: " << thirdDruidicStaff << '\n';
		std::cout << "Total druidic cloaks: " << thirdDruidicCloak << '\n';
		std::cout << "Total master clues completed: " << masterCounter << '\n';
		std::cout << "First master cycle finished\n\n\n";
	}*/

	thirdAgeBox totalValue;
	totalValue.hardClues = hardCounter;
	totalValue.eliteClues = eliteCounter;
	totalValue.masterClues = masterCounter;
	return totalValue;
}

clueBox challengeXericSolo(int option, bool petOnly)
{
	const double RAIDPOINTS = 60000;
	double lootChance = RAIDPOINTS / 867500; // caps at 65.7% chance, shouldn't run into cap solo
	lootChance = round(1 / lootChance);
	int killcount = 0, olmlet = 0, dust = 0, kit = 0, dex = 0, arcane = 0, buckler = 0, cbow = 0, bulwark = 0, hat = 0, robetop = 0, robebottom = 0, claws = 0, maul = 0, kodai = 0, bow = 0,
		clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (olmlet == 0 || dust == 0 || kit < 3 || dex == 0 || arcane == 0 || buckler == 0 || cbow == 0 || bulwark == 0 || hat == 0 || robetop == 0 || robebottom == 0
			|| claws == 0 || maul == 0 || kodai == 0 || bow == 0)
		{
			int intChance = lootChance;
			int dustRoll = rand() % 400 + 1;
			if (dustRoll == 1)
				dust++;
			int kitRoll = rand() % 100 + 1; // Kit rates are not released, this is a guess from what a friend told me
			if (kitRoll == 1)
				kit++;
			int roll = rand() % intChance + 1;
			if (roll == 1)
			{
				int petRoll = rand() % 53 + 1;
				if (petRoll == 1)
					olmlet++;
				int rareRoll = rand() % 69 + 1;
				if (rareRoll < 21)
					dex++;
				else if (rareRoll > 20 && rareRoll < 41)
					arcane++;
				else if (rareRoll > 40 && rareRoll < 45)
					buckler++;
				else if (rareRoll > 44 && rareRoll < 49)
					cbow++;
				else if (rareRoll > 48 && rareRoll < 52)
					bulwark++;
				else if (rareRoll > 51 && rareRoll < 55)
					hat++;
				else if (rareRoll > 54 && rareRoll < 58)
					robetop++;
				else if (rareRoll > 57 && rareRoll < 61)
					robebottom++;
				else if (rareRoll > 60 && rareRoll < 64)
					claws++;
				else if (rareRoll > 63 && rareRoll < 66)
					maul++;
				else if (rareRoll > 65 && rareRoll < 68)
					kodai++;
				else if (rareRoll > 67 && rareRoll < 70)
					bow++;
			}
			killcount++;
			int clueRoll = rand() % 12;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * COXSTANDARD;
		gp += bow * TWISTEDBOW;
		gp += maul * ELDERMAUL;
		gp += kodai * KODAIINSIGNIA;
		gp += hat * ANCESTHAT;
		gp += robetop * ANCESTTOP;
		gp += robebottom * ANCESTLEGS;
		gp += claws * DRAGONCLAWS;
		gp += bulwark * BULWARK;
		gp += cbow * DRAGONHUNTERCBOW;
		gp += buckler * TWISTEDBUCKLER;
		gp += dex * DEXSCROLL;
		gp += arcane * ARCANESCROLL;

		if (option == 1)
		{
			std::cout << "You completed chamber of xerics in " << killcount << " solo challenge mode raids.\n";
			std::cout << "Dusts: " << dust << '\n';
			std::cout << "Kits: " << kit << '\n';
			std::cout << "Olmlets: " << olmlet << '\n';
			std::cout << "Twisted Bows: " << bow << '\n';
			std::cout << "Elder Mauls: " << maul << '\n';
			std::cout << "Kodais: " << kodai << '\n';
			std::cout << "Ancestral Hats: " << hat << '\n';
			std::cout << "Ancestral Robe Tops: " << robetop << '\n';
			std::cout << "Ancestral Robe Bottoms: " << robebottom << '\n';
			std::cout << "Dragon claws: " << claws << '\n';
			std::cout << "Bulwarks: " << bulwark << '\n';
			std::cout << "Dragon Hunter Crossbows: " << cbow << '\n';
			std::cout << "Twisted Bucklers: " << buckler << '\n';
			std::cout << "Dexterous Scrolls: " << dex << '\n';
			std::cout << "Arcane Scrolls: " << arcane << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (olmlet == 0)
		{
			int intChance = lootChance;
			int dustRoll = rand() % 400 + 1;
			if (dustRoll == 1)
				dust++;
			int kitRoll = rand() % 100 + 1; // Kit rates are not released, this is a guess from what a friend told me
			if (kitRoll == 1)
				kit++;
			int roll = rand() % intChance + 1;
			if (roll == 1)
			{
				int petRoll = rand() % 53 + 1;
				if (petRoll == 1)
					olmlet++;
				int rareRoll = rand() % 69 + 1;
				if (rareRoll < 21)
					dex++;
				else if (rareRoll > 20 && rareRoll < 41)
					arcane++;
				else if (rareRoll > 40 && rareRoll < 45)
					buckler++;
				else if (rareRoll > 44 && rareRoll < 49)
					cbow++;
				else if (rareRoll > 48 && rareRoll < 52)
					bulwark++;
				else if (rareRoll > 51 && rareRoll < 55)
					hat++;
				else if (rareRoll > 54 && rareRoll < 58)
					robetop++;
				else if (rareRoll > 57 && rareRoll < 61)
					robebottom++;
				else if (rareRoll > 60 && rareRoll < 64)
					claws++;
				else if (rareRoll > 63 && rareRoll < 66)
					maul++;
				else if (rareRoll > 65 && rareRoll < 68)
					kodai++;
				else if (rareRoll > 67 && rareRoll < 70)
					bow++;
			}
			killcount++;
			int clueRoll = rand() % 12;
			if (clueRoll == 1)
				clue++;
		}

		gp += killcount * COXSTANDARD;
		gp += bow * TWISTEDBOW;
		gp += maul * ELDERMAUL;
		gp += kodai * KODAIINSIGNIA;
		gp += hat * ANCESTHAT;
		gp += robetop * ANCESTTOP;
		gp += robebottom * ANCESTLEGS;
		gp += claws * DRAGONCLAWS;
		gp += bulwark * BULWARK;
		gp += cbow * DRAGONHUNTERCBOW;
		gp += buckler * TWISTEDBUCKLER;
		gp += dex * DEXSCROLL;
		gp += arcane * ARCANESCROLL;

		if (option == 1)
		{
			std::cout << "You completed chamber of xerics in " << killcount << " solo challenge mode raids.\n";
			std::cout << "Dusts: " << dust << '\n';
			std::cout << "Kits: " << kit << '\n';
			std::cout << "Olmlets: " << olmlet << '\n';
			std::cout << "Twisted Bows: " << bow << '\n';
			std::cout << "Elder Mauls: " << maul << '\n';
			std::cout << "Kodais: " << kodai << '\n';
			std::cout << "Ancestral Hats: " << hat << '\n';
			std::cout << "Ancestral Robe Tops: " << robetop << '\n';
			std::cout << "Ancestral Robe Bottoms: " << robebottom << '\n';
			std::cout << "Dragon claws: " << claws << '\n';
			std::cout << "Bulwarks: " << bulwark << '\n';
			std::cout << "Dragon Hunter Crossbows: " << cbow << '\n';
			std::cout << "Twisted Bucklers: " << buckler << '\n';
			std::cout << "Dexterous Scrolls: " << dex << '\n';
			std::cout << "Arcane Scrolls: " << arcane << '\n';
			std::cout << "Total gp earned: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox theater(int option, bool petOnly) // assumes no deaths for whole team, team of 3
{
	int killcount = 0, hilt = 0, rapier = 0, staff = 0, helm = 0, chest = 0, legs = 0, scythe = 0, pet = 0, seenHilt = 0, seenRapier = 0, seenStaff = 0, seenHelm = 0, seenChest = 0,
		seenLegs = 0, seenScythe = 0, seenPet = 0, clue = 0;
	double gp = 0;
	if (petOnly == 0)
	{
		while (hilt == 0 || rapier == 0 || staff == 0 || helm == 0 || chest == 0 || legs == 0 || scythe == 0 || pet == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				int petRoll = rand() % 650 + 1;
				if (petRoll == 1)
				{
					if (i == 1)
						pet++;
					else
						seenPet++;
				}
			}

			int roll = rand() % 91 + 1;
			if (roll < 11)
			{
				int playerRoll = rand() % 3 + 1;
				int roll2 = rand() % 19 + 1;
				if (roll2 == 1)
				{
					if (playerRoll == 1)
						scythe++;
					else
						seenScythe++;
				}
				else if (roll2 > 1 && roll2 < 4)
				{
					if (playerRoll == 1)
						rapier++;
					else
						seenRapier++;
				}
				else if (roll2 > 3 && roll2 < 6)
				{
					if (playerRoll == 1)
						staff++;
					else
						seenStaff++;
				}
				else if (roll2 > 5 && roll2 < 8)
				{
					if (playerRoll == 1)
						helm++;
					else
						seenHelm++;
				}
				else if (roll2 > 7 && roll2 < 10)
				{
					if (playerRoll == 1)
						chest++;
					else
						seenChest++;
				}
				else if (roll2 > 9 && roll2 < 12)
				{
					if (playerRoll == 1)
						legs++;
					else
						seenLegs++;
				}
				else if (roll2 > 11)
				{
					if (playerRoll == 1)
						hilt++;
					else
						seenHilt++;
				}
			}
			killcount++;
			int clueRoll = rand() % 83;
			if (clueRoll < 10)
				clue++;
		}

		gp += killcount * TOBSTANDARD;
		gp += ((scythe + seenScythe) * VITURSCYTHE) / 3;
		gp += ((rapier + seenRapier) * GHRAZIRAPIER) / 3;
		gp += ((staff + seenStaff) * SANGSTAFF) / 3;
		gp += ((helm + seenHelm) * JUSTICIARHELM) / 3;
		gp += ((chest + seenChest) * JUSTICIARPLATE) / 3;
		gp += ((legs + seenLegs) * JUSTICIARLEGS) / 3;
		gp += ((hilt + seenHilt) * AVERNICHILT) / 3;

		if (option == 1)
		{
			std::cout << "You finished the Theater of Blood in " << killcount << " completions.\n";
			std::cout << "Lil Ziks: " << pet << " and you saw other people get Lil Zik " << seenPet << " times.\n";
			std::cout << "Your Scythes: " << scythe << " and you saw " << seenScythe << " other scythes.\n";
			std::cout << "Your Rapiers: " << rapier << " and you saw " << seenRapier << " other rapiers.\n";
			std::cout << "Your Sanguinesti Staves: " << staff << " and you saw " << seenStaff << " other staves.\n";
			std::cout << "Your Justiciar Faceguards: " << helm << " and you saw " << seenHelm << " other helms.\n";
			std::cout << "Your Justiciar Chestguards: " << chest << " and you saw " << seenChest << " other chests.\n";
			std::cout << "Your Justiciar Legguards: " << legs << " and you saw " << seenLegs << " other legs.\n";
			std::cout << "Your Avernic Hilts: " << hilt << " and you saw " << seenHilt << " other hilts.\n";
			std::cout << "Your total earned gp was: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
	else
	{
		while (pet == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				int petRoll = rand() % 650 + 1;
				if (petRoll == 1)
				{
					if (i == 1)
						pet++;
					else
						seenPet++;
				}
			}

			int roll = rand() % 91 + 1;
			if (roll < 11)
			{
				int playerRoll = rand() % 3 + 1;
				int roll2 = rand() % 19 + 1;
				if (roll2 == 1)
				{
					if (playerRoll == 1)
						scythe++;
					else
						seenScythe++;
				}
				else if (roll2 > 1 && roll2 < 4)
				{
					if (playerRoll == 1)
						rapier++;
					else
						seenRapier++;
				}
				else if (roll2 > 3 && roll2 < 6)
				{
					if (playerRoll == 1)
						staff++;
					else
						seenStaff++;
				}
				else if (roll2 > 5 && roll2 < 8)
				{
					if (playerRoll == 1)
						helm++;
					else
						seenHelm++;
				}
				else if (roll2 > 7 && roll2 < 10)
				{
					if (playerRoll == 1)
						chest++;
					else
						seenChest++;
				}
				else if (roll2 > 9 && roll2 < 12)
				{
					if (playerRoll == 1)
						legs++;
					else
						seenLegs++;
				}
				else if (roll2 > 11)
				{
					if (playerRoll == 1)
						hilt++;
					else
						seenHilt++;
				}
			}
			killcount++;
			int clueRoll = rand() % 83;
			if (clueRoll < 10)
				clue++;
		}

		gp += killcount * TOBSTANDARD;
		gp += ((scythe + seenScythe) * VITURSCYTHE) / 3;
		gp += ((rapier + seenRapier) * GHRAZIRAPIER) / 3;
		gp += ((staff + seenStaff) * SANGSTAFF) / 3;
		gp += ((helm + seenHelm) * JUSTICIARHELM) / 3;
		gp += ((chest + seenChest) * JUSTICIARPLATE) / 3;
		gp += ((legs + seenLegs) * JUSTICIARLEGS) / 3;
		gp += ((hilt + seenHilt) * AVERNICHILT) / 3;

		if (option == 1)
		{
			std::cout << "You finished the Theater of Blood in " << killcount << " completions.\n";
			std::cout << "Lil Ziks: " << pet << " and you saw other people get Lil Zik " << seenPet << " times.\n";
			std::cout << "Your Scythes: " << scythe << " and you saw " << seenScythe << " other scythes.\n";
			std::cout << "Your Rapiers: " << rapier << " and you saw " << seenRapier << " other rapiers.\n";
			std::cout << "Your Sanguinesti Staves: " << staff << " and you saw " << seenStaff << " other staves.\n";
			std::cout << "Your Justiciar Faceguards: " << helm << " and you saw " << seenHelm << " other helms.\n";
			std::cout << "Your Justiciar Chestguards: " << chest << " and you saw " << seenChest << " other chests.\n";
			std::cout << "Your Justiciar Legguards: " << legs << " and you saw " << seenLegs << " other legs.\n";
			std::cout << "Your Avernic Hilts: " << hilt << " and you saw " << seenHilt << " other hilts.\n";
			std::cout << "Your total earned gp was: " << gp << '\n';
		}
		clueBox returnCounters;
		returnCounters.return1 = killcount;
		returnCounters.return2 = gp;
		returnCounters.return3 = clue;
		return returnCounters;
	}
}

clueBox chinchompa(int option) //assumes level 99 hunter, also not exact as mod large numbers seems to give bad results, so broken down into smaller chunks, original number has too large a prime in it
{
	int pet = 0, blackChin = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 223 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 24 + 1;
			if (roll2 == 1)
			{
				int roll3 = rand() % 15 + 1;
				if (roll3 == 1)
					pet++;
			}
		}
		blackChin++;
	}

	gp += blackChin * BLACKCHIN;

	if (option == 1)
	{
		std::cout << "You caught " << blackChin << " black chinchompas before getting your baby chinchompa!\n";
		std::cout << "You gained " << blackChin * 315 << " hunter experience!\n";
		std::cout << "It took you " << blackChin / 625 << " hours.\n";
	}
	clueBox returnCounters;
	returnCounters.return1 = blackChin;
	returnCounters.return2 = gp;
	return returnCounters;
}

clueBox beaver(int option) // assumes 99 wc, teaks
{
	int pet = 0, teakLogs = 0, clue = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 457 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 573 + 1;
			if (roll2 == 1)
				pet++;
		}
		teakLogs++;
		int clueRoll = rand() % 182;
		if (clueRoll == 1)
		{
			int clueRoll2 = rand() % 107;
			if (clueRoll2 == 1)
				clue++;
		}
	}

	gp += teakLogs * WOODCUTSTANDARD;

	if (option == 1)
	{
		std::cout << "You chopped " << teakLogs << " teak logs to get your beaver!\n";
		std::cout << "You gained " << teakLogs * 85 << " woodcutting exp getting your beaver!\n";
		std::cout << "It took you " << teakLogs / 2350 << " hours.\n";
		std::cout << "Crystal shards used: " << teakLogs / 100 << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = teakLogs;
	returnCounters.return2 = gp;
	returnCounters.return3 = clue;
	return returnCounters;
}

int squirrel(int option)
{
	int laps = 0, pet = 0;
	while (pet == 0)
	{
		int roll = rand() % 83 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 88 + 1;
			if (roll2 == 1)
				pet++;
		}
		laps++;
	}
	if (option == 1)
	{
		std::cout << "You completed " << laps << " laps at the penguin course to get your Giant Squirrel!\n";
		std::cout << "You gained " << laps * 540 << " agility experience while getting your squirrel!\n";
		std::cout << "It took you " << (laps * 65) / 3600 << " hours to get your squirrel!\n";
	}
	return laps;
}

clueBox heron(int option)
{
	int pet = 0, swordies = 0, clue = 0;   // about 53% tuna 47% swordies distribution
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 100 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 79 + 1;
			if (roll2 == 1)
			{
				int roll3 = rand() % 16 + 1;
				if (roll3 == 1)
					pet++;
			}
		}
		swordies++;
		int clueRoll = rand() % 168;
		{
			if (clueRoll == 1)
			{
				int clueRoll2 = rand() % 113;
				if (clueRoll2 == 1)
					clue++;
			}
		}
	}

	gp += swordies * FISHINGSTANDARD;

	if (option == 1)
	{
		std::cout << "You fished " << swordies << " swordies/tunas to get your heron!\n";
		std::cout << "You gained " << swordies * 93 << " fishing experience while getting your heron!\n";
		std::cout << "It took " << swordies / 1500 << " hours to get your heron!\n";
	}
	clueBox returnCounters;
	returnCounters.return1 = swordies;
	returnCounters.return2 = gp;
	returnCounters.return3 = clue;
	return returnCounters;
}

int rift(int option)
{
	int pet = 0; // VERY CLOSE BUT NOT EXACT!!!!!!!! ASSUMING 99 rc, 1,793,283 rate for pet, assumed 23 ess/inv average, 1,793,283 / 23 = 77,968.82609, we will be rounding to nearest int as rate(77,968)
	double minds = 0;
	while (pet == 0)
	{
		int roll = rand() % 8 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 22 + 1; // Errors found when using large rand numbers, therefore broken down into multiple smaller rolls
			if (roll2 == 1)
			{
				int roll3 = rand() % 443 + 1;
				if (roll3 == 1)
					pet++;
			}
		}
		minds++; // Inventory done each time counter is increased, 2x invs per run, not individual essence
	}
	//if ((minds * 23) / 1793264 < 0.0002)
	//	std::cout << "Rarer than 1/5000 hit for guardian " << minds * 23 << " ess crafted for pet.\n";
	if (option == 1)
	{
		std::cout << "You runecrafted " << minds * 23 << " ess into mind runes to get your rift guardian!\n";
		std::cout << "You gained " << floor(minds * 5.5 * 23) << " runecrafting exp while getting your guardian!\n";
		std::cout << "You spent " << (minds * 23) / 10476 << " hours getting your guardian!\n";
	}
	return minds;
}

clueBox golem(int option)
{
	int pet = 0, gems = 0, clue = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 349 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 100 + 1;
			if (roll2 == 1)
			{
				int roll3 = rand() % 6 + 1;
				if (roll3 == 1)
					pet++;
			}
		}
		gems++;
		int clueRoll = rand() % 223;
		if (clueRoll == 1)
		{
			int clueRoll2 = rand() % 70;
			if (clueRoll2 == 1)
				clue++;
		}
	}
	
	gp += MININGSTANDARD * gems;

	if (option == 1)
	{
		std::cout << "You mined " << gems << " gems while getting your rock golem!\n";
		std::cout << "You gained " << gems * 65 << " mining exp while getting your golem!\n";
		std::cout << "You spent " << gems / 1300 << " hours getting your golem!\n";
	}
	clueBox returnCounters;
	returnCounters.return1 = gems;
	returnCounters.return2 = gp;
	returnCounters.return3 = clue;
	return returnCounters;
}

int rocky(int option)
{
	int pet = 0;
	double stalls = 0;
	while (pet == 0)
	{
		int roll = rand() % 25 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 40 + 1;
			if (roll2 == 1)
			{
				int roll3 = rand() % 34 + 1;
				if (roll3 == 1)
					pet++;
			}
		}
		stalls++;
	}
	if (option == 1)
	{
		std::cout << "You looted " << stalls << " fur/fish stalls to get rocky!\n";
		std::cout << "You gained " << stalls * 39.8 << " thieving exp while getting rocky!\n";
		std::cout << "You spent " << stalls / 1280 << " hours looting stalls to get rocky!\n";
	}
	return stalls;
}

clueBox tangle(int option) // 99 farm assumed
{
	int pet = 0, day = 0, mahogany = 0, hespori = 0, fruit = 0, redwood = 0, mage = 0, crystal = 0, calquat = 0;
	double gp = 0;
	while (pet == 0)
	{
		day++;
		// go through a day of farm runs
		mahogany++;
		int hardwood = rand() % 101 + 1;
		if (hardwood == 1)
		{
			int hardwood2 = rand() % 25 + 1;
			if (hardwood2 == 1)
			{
				pet++;
				break;
			}
		}

		hespori++;
		int hesporiRoll = rand() % 181 + 1;
		if (hesporiRoll == 1)
		{
			int hespori2 = rand() % 25 + 1;
			if (hespori2 == 1)
			{
				pet++;
				break;
			}
		}

		for (int i = 0; i < 6; i++)
		{
			fruit++;
			int fruitRoll = rand() % 261 + 1;
			if (fruitRoll == 1)
			{
				int fruitRoll2 = rand() % 25 + 1;
				if (fruitRoll2 == 1)
				{
					pet++;
					break;
				}
			}
		}
		if (pet > 0)
			break;

		int dayRoll = rand() % 44 + 1;
		if (dayRoll < 11)
		{
			redwood++;
			int redwoodRoll = rand() % 101 + 1;
			if (redwoodRoll == 1)
			{
				int redwoodRoll2 = rand() % 25 + 1;
				if (redwoodRoll2 == 1)
				{
					pet++;
					break;
				}
			}
		}

		for (int i = 0; i < 12; i++)
		{
			mage++;
			int mageRoll = rand() % 113 + 1;
			if (mageRoll == 1)
			{
				int mageRoll2 = rand() % 61 + 1;
				if (mageRoll2 == 1)
				{
					pet++;
					break;
				}
			}
		}
		if (pet > 0)
			break;

		for (int i = 0; i < 2; i++)
		{
			crystal++;
			int crystalRoll = rand() % 261 + 1;
			if (crystalRoll == 1)
			{
				int crystalRoll2 = rand() % 25 + 1;
				if (crystalRoll2 == 1)
				{
					pet++;
					break;
				}
			}
		}
		if (pet > 0)
			break;

		calquat++;
		int calquatRoll = rand() % 141 + 1;
		if (calquatRoll == 1)
		{
			int calquatRoll2 = rand() % 25 + 1;
			if (calquatRoll2 == 1)
			{
				pet++;
			}
		}
	}

	gp += mahogany * MAHOGANYSEED;
	gp += fruit * FRUITSEED;
	gp += redwood * REDWOODSEED;
	gp += calquat * CALQSEED;
	gp += mage * MAGICSEED;
	if (crystal > 400) // crystal shard cost already used for crystal tools, if each pet is obtained at rate it takes 400 crystal trees to fund
		gp += (crystal - 400) * CRYSTALSEED;
	gp += calquat * CALQSEED;

	if (option == 1)
	{
		std::cout << "You finished the tangleroot pet in " << day << " days.\n";
		std::cout << "You gained " << mahogany * 15783 + hespori * 12600 + fruit * 17475 + redwood * 22680 + calquat * 12226 + mage * 13914 + crystal * 13366 <<
			" farming exp while getting tangleroot!\n";
		std::cout << "Mahogany trees: " << mahogany << '\n';
		std::cout << "Hespori: " << hespori << '\n';
		std::cout << "Dragonfruit trees: " << fruit << '\n';
		std::cout << "Redwood trees: " << redwood << '\n';
		std::cout << "Calquat trees: " << calquat << '\n';
		std::cout << "Mage trees: " << mage << '\n';
		std::cout << "Crystal trees: " << crystal << '\n';
		std::cout << "Total gp spent: " << gp << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = day;
	returnCounters.return2 = gp;
	return returnCounters;
}

int chompy(int option)
{
	int pet = 0, killcount = 0;
	while (pet == 0)
	{
		int roll = rand() % 500 + 1;
		if (roll == 1)
			pet++;
		killcount++;
	}
	if (option == 1)
	{
		std::cout << "You killed " << killcount << " chompy birds to get your chompy chick!\n";
		std::cout << "It took you " << killcount / 150 << " hours to get your chompy chicke!\n";
	}
	return killcount;
}

clueBox herbi(int option)
{
	int pet = 0, killcount = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 100 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 65 + 1;
			if (roll2 == 1)
				pet++;
		}
		killcount++;
	}

	gp += killcount * HERBISTANDARD;

	if (option == 1)
	{
		std::cout << "You hunted " << killcount << " herbiboars to get your herbi pet!\n";
		std::cout << "It took you " << killcount / 60 << " hours to get your herbi pet!\n";
	}
	clueBox returnCounters;
	returnCounters.return1 = killcount;
	returnCounters.return2 = gp;
	return returnCounters;
}

clueBox penance(int option)
{
	int killcount = 0, pet = 0, clue = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 100 + 1;
		if (roll == 1)
		{
			int roll2 = rand() % 10 + 1;
			if (roll2 == 1)
				pet++;
		}
		killcount++;
		int clueRoll = rand() % 15;
		if (clueRoll == 1)
			clue++;
	}

	gp += killcount * BAHIGHGAMBLE;

	if (option == 1)
	{
		std::cout << "You did " << killcount << " high gambles to get your penance pet!\n";
		std::cout << "It took you " << killcount / 2 << " hours to get your penance pet!\n";
	}
	clueBox returnCounters;
	returnCounters.return1 = killcount;
	returnCounters.return2 = gp;
	returnCounters.return3 = clue;
	return returnCounters;
}

clueBox zuk(int option)
{
	int killcount = 0, pet = 0, cape = 0;
	double gp = 0;
	while (pet == 0)
	{
		int roll = rand() % 75 + 1;
		cape++;
		if (roll == 1)
			pet++;
		if (pet == 0)
		{
			int roll2 = rand() % 100 + 1;
			cape--;
			if (roll2 == 1)
				pet++;
		}
		killcount++;
	}

	gp += killcount * ZUKSTANDARD;

	if (option == 1)
	{
		std::cout << "You finished Zuk in " << killcount << " kills.\n";
		std::cout << "Total inferno capes left: " << cape << '\n';
	}
	clueBox returnCounters;
	returnCounters.return1 = killcount;
	returnCounters.return2 = gp;
	return returnCounters;
}

petBox petRun(int option, bool talk)
{
	clueBox armadylResults, sireResults, todResults, zulrahResults, hydraResults, corpResults, vorkathResults, cerbResults, callistoResults, nightmareResults, theaterResults, olmletResults,
		gauntResults, heronResult, beaverResults, chinResults, graardorResults, zilyanaResults, eleResults, sarachnisResults, jadResults, thermyResults, scorpiaResults, skotosResults,
		venenatisResults, vetionResults, golemResults, tangleResults, herbiResults, zukResults, penanceResults, zalcanoResults, krakenResults, moleResults, kqResults, noonResults, krilResults,
		kbdResults;
	double move = 0, squirrelResult = 0, riftResults = 0, rockyResults = 0,
		houndResults = 0, gp = 0, freeElites = 0;
	double petDropRateSum = 0, time = 0, worstRate, bestRate, dropRate;
	dagBox dagResults;
	if (talk == 0)
	{
		std::cout << "Time to start the journey to all pets! This is going to be fun! Wish me luck!\n";
		std::cout << "Our young adventurer has decided to embark on the long journey to obtain every pet drop...\n\n";
		std::cout << "I'll start my journey by training my skills up and getting the skilling pets first!\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
	{
		std::cout << "We're going to start with fishing! Let's head over to the swordfish...\n\n";
	}

	if (option == 1)
		std::cin >> move;
	if (talk == 0)
		heronResult = heron(1);
	else
		heronResult = heron(0);
	dropRate = heronResult.return1 / 126410;
	petDropRateSum += dropRate;
	time += heronResult.return1 / 1500;
	gp += heronResult.return2;
	freeElites += heronResult.return3;
	worstRate = dropRate;
	bestRate = dropRate;
	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWell, that was fun, 1 down, many to go, let's move onto the giant squirrel, agility is super useful!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		squirrelResult = squirrel(1);
	else
		squirrelResult = squirrel(0);
	dropRate = squirrelResult / 7304;
	petDropRateSum += dropRate;
	time += squirrelResult / 52;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;
	
	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nI'm getting the hang of this, onto the next! Let's knock out the rift guardian now, its a tough one!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		riftResults = rift(1);
	else
		riftResults = rift(0);
	dropRate = (riftResults * 23) / 1793283;
	petDropRateSum += dropRate;
	time += (riftResults * 23) / 10476;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;
	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nSweet but sad feeling... being done with runecrafting. Let's move onto the beaver next.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		beaverResults = beaver(1);
	else
		beaverResults = beaver(0);
	dropRate = beaverResults.return1 / 261861;
	petDropRateSum += dropRate;
	time += beaverResults.return1 / 2059;
	gp += beaverResults.return2;
	freeElites += beaverResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWe're almost done with the skilling pets already! Let's move onto an easy one next--Rocky!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		rockyResults = rocky(1);
	else
		rockyResults = rocky(0);
	dropRate = rockyResults / 34015;
	petDropRateSum += dropRate;
	time += rockyResults / 1280;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWow I have a loyal racoon now, let's go get us some money and a baby chinchompa next!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		chinResults = chinchompa(1);
	else
		chinResults = chinchompa(0);

	dropRate = chinResults.return1 / 80283;
	petDropRateSum += dropRate;
	time += chinResults.return1 / 793;
	gp += chinResults.return2;
	freeElites += chinResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nI made some pretty good money from that, but I'm tired of those pkers, let's please move to something else, how about the rock golem!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		golemResults = golem(1);
	else
		golemResults = golem(0);
	dropRate = golemResults.return1 / 209411;
	petDropRateSum += dropRate;
	time += golemResults.return1 / 1300;
	gp += golemResults.return2;
	freeElites += golemResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nMining down, just about done with skilling!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		tangleResults = tangle(1);
	else
		tangleResults = tangle(0);

	dropRate = tangleResults.return1 / 270;
	petDropRateSum += dropRate;
	time += tangleResults.return1 / 2;
	gp += tangleResults.return2;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nTangle done! A lot of that was done while doing other pets, now we'll mve onto a semi-skilling pet which is herbi!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		herbiResults = herbi(1);
	else
		herbiResults = herbi(0);

	dropRate = herbiResults.return1 / 6500;
	time += herbiResults.return1 / 62;
	petDropRateSum += dropRate;
	gp += herbiResults.return2;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWe're almost done with all them skilling pets! Let's move onto phoenix!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		todResults = wintertodt(1, 1);
	else
		todResults = wintertodt(0, 1);

	dropRate = todResults.return1 / 178.6;
	time += todResults.return1 / 1.2;
	petDropRateSum += dropRate;
	gp += todResults.return2;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nAll skilling pets done! It's time to boss baby! We'll start with the slayer pets.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		sireResults = abyssalSire(1, 1);
	else
		sireResults = abyssalSire(0, 1);
	dropRate = sireResults.return1 / 2560;
	time += sireResults.return1 / 34;
	petDropRateSum += dropRate;
	gp += sireResults.return2;
	freeElites += sireResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nMy first boss pet done! I'm getting pretty good at this! Kraken up next.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		krakenResults = kraken(1, 1);
	else
		krakenResults = kraken(0, 1);
	dropRate = krakenResults.return1 / 3000;
	time += krakenResults.return1 / 90;
	petDropRateSum += dropRate;
	gp += krakenResults.return2;
	freeElites += krakenResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\n12 pets done? Am I a pro at this yet? Cerberus up next!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		cerbResults = cerberus(1, 1);
	else
		cerbResults = cerberus(0, 1);
	dropRate = cerbResults.return1 / 3000;
	time += cerbResults.return1 / 45;
	petDropRateSum += dropRate;
	gp += cerbResults.return2;
	freeElites += cerbResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWe're trucking along... We move to yet another pet--Hydra!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		hydraResults = alchemicalHydra(1, 1);
	else
		hydraResults = alchemicalHydra(0, 1);
	dropRate = hydraResults.return1 / 3000;
	time += hydraResults.return1 / 27;
	petDropRateSum += dropRate;
	gp += hydraResults.return2;
	freeElites += hydraResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nLet's go! Bank was made and we keep trucking.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		jadResults = jad(1);
	else
		jadResults = jad(0);
	dropRate = jadResults.return1 / 67;
	time += jadResults.return1 / 2;
	petDropRateSum += dropRate;
	gp += jadResults.return2;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWow! We got a jad pet! We're going to beat the hard version now! Zuk I'm coming for you.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		zukResults = zuk(1);
	else
		zukResults = zuk(0);
	dropRate = zukResults.return1 / 43;
	time += zukResults.return1 / 0.8;
	petDropRateSum += dropRate;
	gp += zukResults.return2;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nThat is a sweet pet! We've got 1 of the best, we must be a pro pet hunter now!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		noonResults = grotGuardians(1, 1);
	else
		noonResults = grotGuardians(0, 1);
	dropRate = noonResults.return1 / 3000;
	time += noonResults.return1 / 30;
	petDropRateSum += dropRate;
	gp += noonResults.return2;
	freeElites += noonResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nThat boss sucked! I'm glad to be done. Thermy up next!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		thermyResults = thermy(1, 1);
	else
		thermyResults = thermy(0, 1);
	dropRate = thermyResults.return1 / 3000;
	time += thermyResults.return1 / 110;
	petDropRateSum += dropRate;
	gp += thermyResults.return2;
	freeElites += thermyResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nI'm nearing the 20 pets massive milestone. It's been a long journey...\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		skotosResults = skotizo(1, 1);
	else
		skotosResults = skotizo(0, 1);
	dropRate = skotosResults.return1 / 65;
	time += skotosResults.return1 / 0.6;
	petDropRateSum += dropRate;
	gp += skotosResults.return2;
	freeElites += skotosResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nAll slayer pets done! Now I can finally play for real! Cox next to make some bank!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		olmletResults = challengeXericSolo(1, 1);
	else
		olmletResults = challengeXericSolo(0, 1);
	dropRate = olmletResults.return1 / 766;
	time += olmletResults.return1 / 0.95;
	petDropRateSum += dropRate;
	gp += olmletResults.return2;
	freeElites += olmletResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\n20 Pets done. A very very long grind over... I have the olmlet! I made bank aswell. Pleb no longer. I'm going to do theater now!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		theaterResults = theater(1, 1);
	else
		theaterResults = theater(0, 1);
	dropRate = theaterResults.return1 / 650;
	time += theaterResults.return1 / 3;
	petDropRateSum += dropRate;
	gp += theaterResults.return2;
	freeElites += theaterResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWow! That was way better than cox, more money and quicker. Raids complete and now onto dks.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		dagResults = dags(1, 1);
	else
		dagResults = dags(0, 1);
	dropRate = dagResults.rex1 / 5000;
	time += dagResults.rex1 / 88;
	petDropRateSum += dropRate;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	dropRate = dagResults.supreme1 / 5000;
	time += dagResults.supreme1 / 88;
	petDropRateSum += dropRate;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	dropRate = dagResults.prime1 / 5000;
	time += dagResults.prime1 / 88;
	petDropRateSum += dropRate;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	gp += dagResults.gp;
	freeElites += dagResults.clue;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nThe iconic dags are done, all three pets obtained! Let's do some kalphite queen then kbd!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		kqResults = kalphiteQueen(1, 1);
	else
		kqResults = kalphiteQueen(0, 1);
	dropRate = kqResults.return1 / 3000;
	time += kqResults.return1 / 35;
	petDropRateSum += dropRate;
	gp += kqResults.return2;
	freeElites += kqResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nBugs have been slain and we shall continue the journey!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		kbdResults = kbd(1, 1);
	else
		kbdResults = kbd(0, 1);
	dropRate = kbdResults.return1 / 3000;
	time += kbdResults.return1 / 110;
	petDropRateSum += dropRate;
	gp += kbdResults.return2;
	freeElites += kbdResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nI've done more than half of the pets! It's been a long road... and there's still much to go...\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		callistoResults = callisto(1, 1);
	else
		callistoResults = callisto(0, 1);
	dropRate = callistoResults.return1 / 2000;
	time += callistoResults.return1 / 30;
	petDropRateSum += dropRate;
	gp += callistoResults.return2;
	freeElites += callistoResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nThat's one wilderness pet down and we'll continue and finish off the others!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		vetionResults = vetion(1, 1);
	else
		vetionResults = vetion(0, 1);
	dropRate = vetionResults.return1 / 2000;
	time += vetionResults.return1 / 30;
	petDropRateSum += dropRate;
	gp += vetionResults.return2;
	freeElites += vetionResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nAnother wilderness pet down! One more to go!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		venenatisResults = venenatis(1, 1);
	else
		venenatisResults = venenatis(0, 1);
	dropRate = venenatisResults.return1 / 2000;
	time += venenatisResults.return1 / 44;
	petDropRateSum += dropRate;
	gp += venenatisResults.return2;
	freeElites += venenatisResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nAnother set of pets complete! That is a nice achievement!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		moleResults = mole(1);
	else
		moleResults = mole(0);
	dropRate = moleResults.return1 / 3000;
	time += moleResults.return1 / 80;
	petDropRateSum += dropRate;
	gp += moleResults.return2;
	freeElites += moleResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nAn easy one knocked out quick! Let's do another quick one, chaos fanatic next!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		eleResults = chaosEle(1);
	else
		eleResults = chaosEle(0);
	dropRate = eleResults.return1 / 300;
	time += eleResults.return1 / 60;
	petDropRateSum += dropRate;
	gp += eleResults.return2;
	freeElites += eleResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nSuper easy! We've got to be a top pet hunter now right? Let's go do some Zulrah.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		zulrahResults = zulrah(1, 1);
	else
		zulrahResults = zulrah(0, 1);
	dropRate = zulrahResults.return1 / 4000;
	time += zulrahResults.return1 / 35;
	petDropRateSum += dropRate;
	gp += zulrahResults.return2;
	freeElites += zulrahResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nMoney snake complete! I think it's time for gwd, lets smash it!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		graardorResults = graardor(1, 1);
	else
		graardorResults = graardor(0, 1);
	dropRate = graardorResults.return1 / 5000;
	time += graardorResults.return1 / 30;
	petDropRateSum += dropRate;
	gp += graardorResults.return2;
	freeElites += graardorResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nFirst one done... this is going to be long but the most elite pet set? Kreeeee\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		armadylResults = armadyl(1, 1);
	else
		armadylResults = armadyl(0, 1);
	dropRate = armadylResults.return1 / 5000;
	time += armadylResults.return1 / 25;
	petDropRateSum += dropRate;
	gp += armadylResults.return2;
	freeElites += armadylResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nKree was a fun one, lets get to the demon.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		krilResults = kril(1, 1);
	else
		krilResults = kril(0, 1);
	dropRate = krilResults.return1 / 5000;
	time += krilResults.return1 / 40;
	petDropRateSum += dropRate;
	gp += krilResults.return2;
	freeElites += krilResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWow, 3 of the 4 done... we've actually almost done it!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		zilyanaResults = zily(1, 1);
	else
		zilyanaResults = zily(0, 1);

	dropRate = zilyanaResults.return1 / 5000;
	time += zilyanaResults.return1 / 45;
	petDropRateSum += dropRate;
	gp += zilyanaResults.return2;
	freeElites += zilyanaResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nWe've done it! Huge milestone down! We've completed the gwd pet set!!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		nightmareResults = nightmare(1, 1);
	else
		nightmareResults = nightmare(0, 1);
	dropRate = nightmareResults.return1 / 3950;
	time += nightmareResults.return1 / 15;
	petDropRateSum += dropRate;
	gp += nightmareResults.return2;
	freeElites += nightmareResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nBonk! This journey has been crazy... we're winding down.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		corpResults = corp(1, 1);
	else
		corpResults = corp(0, 1);
	dropRate = corpResults.return1 / 5000;
	time += corpResults.return1 / 45;
	petDropRateSum += dropRate;
	gp += corpResults.return2;
	freeElites += corpResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nAnother hard one done... I'm feeling uneasy because this great journey is about to come to an end...\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		scorpiaResults = scorpia(1, 1);
	else
		scorpiaResults = scorpia(0, 1);
	dropRate = scorpiaResults.return1 / 2016;
	time += scorpiaResults.return1 / 100;
	petDropRateSum += dropRate;
	gp += scorpiaResults.return2;
	freeElites += scorpiaResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nIt's been such a long journey... From nothing to one of the top pet hunters!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		sarachnisResults = sarachnis(1, 1);
	else
		sarachnisResults = sarachnis(0, 1);
	dropRate = sarachnisResults.return1 / 3000;
	time += sarachnisResults.return1 / 60;
	petDropRateSum += dropRate;
	gp += sarachnisResults.return2;
	freeElites += sarachnisResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nOnly a few more! Vorkath next!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		vorkathResults = vorkath(1, 1);
	else
		vorkathResults = vorkath(0, 1);
	dropRate = vorkathResults.return1 / 3000;
	time += vorkathResults.return1 / 32;
	petDropRateSum += dropRate;
	gp += vorkathResults.return2;
	freeElites += vorkathResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\n!Wow! I only have 4 pets left... what is this insanity!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		gauntResults = gauntlet(1, 1);
	else
		gauntResults = gauntlet(0, 1);
	dropRate = gauntResults.return1 / 800;
	time += gauntResults.return1 / 6;
	petDropRateSum += dropRate;
	gp += gauntResults.return2;
	freeElites += gauntResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nGlad to have that one done... But I don't want this to end...\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		zalcanoResults = zalcano(1, 1);
	else
		zalcanoResults = zalcano(0, 1);
	dropRate = zalcanoResults.return1 / 2250;
	time += zalcanoResults.return1 / 18.5;
	petDropRateSum += dropRate;
	gp += zalcanoResults.return2;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nI only have one left... should I just not do it? That way I can keep killing bosses forever and never finish!\n\n";
	}

	if (option == 1)
		std::cin >> move;

	if (talk == 0)
		penanceResults = penance(1);
	else
		penanceResults = penance(0);
	dropRate = penanceResults.return1 / 1000;
	time += penanceResults.return1 / 2.5;
	petDropRateSum += dropRate;
	gp += penanceResults.return2;
	freeElites += penanceResults.return3;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum << " and current gp gained: " << gp;

		std::cout << "\nI currently have " << freeElites << " free elites from previous activities.\n";

		std::cout << "\nThe anxiousness is kicking in, what will I do when I finish...?\n";

		std::cout << "Up next is the hound, we currently have " << freeElites << " free elites from previous activities.\n\n";
	}

	if (option == 1)
		std::cin >> move;

	double gpHolder = gp;

	if (talk == 0)
		houndResults = masterClue(1, 1).return1;
	else
		houndResults = masterClue(0, 1).return1;
	dropRate = houndResults / 1000;
	if (freeElites > houndResults)
		time += houndResults / 4;
	else
	{
		time += freeElites / 4;
		int tempElites = houndResults - freeElites;
		while (tempElites > 0)
		{
			if (gp > 6750000)
			{
				gp -= 6750000;
				time += 0.25;
			}
			else
				time += 0.7;

			tempElites--;
		}
	}
	petDropRateSum += dropRate;
	if (dropRate > worstRate)
		worstRate = dropRate;
	if (dropRate < bestRate)
		bestRate = dropRate;

	if (bestRate == 0)
		std::cout << "We have a problem! A pet rate of 0 occurred!\n";

	if (talk == 0)
	{
		std::cout << "Pet drop rate sum: " << petDropRateSum;

		std::cout << "\nI'm done!!!!!!!!!!!!!!!!! Let's go!!!!!!!! All pets are now complete!!!!!!!!!!!!!!!!\n\n";

		std::cout << "All kills and skilling was done extremely efficiently btw. Total hours to finish: " << time << '\n';

		std::cout << "In the end I came out with " << gp << " gp.\n";

		std::cout << "The average multiple of drop rate for pets: " << petDropRateSum / 46 << '\n';

		std::cout << "My worst luck was " << worstRate << " x the drop rate.\n";

		std::cout << "My best luck was " << bestRate << " x the drop rate.\n";
	}

	if (option == 1)
		std::cin >> move;

	petBox returnValues;
	returnValues.time = time;
	returnValues.petDropRate = petDropRateSum / 46;
	returnValues.worstRate = worstRate;
	returnValues.bestRate = bestRate;
	returnValues.finishedGp = gp;
	returnValues.finishedBonusElites = freeElites;
	returnValues.finishedGpBeforeHound = gpHolder;

	return returnValues;
}

thirdAgeBox efficientThirdAgeTwo(int option)
{
	// Clue table reference: https://docs.google.com/spreadsheets/d/16pVNHdZyynmxIbM9mynRDYT0LQsWxq-vbDs4_7DpnGM/edit#gid=2000272069
	// mmic table reference: https://twitter.com/JagexAsh/status/1158655373378805760
	// MASTER CLUES
	// MASTER CLUES
	// MASTER CLUES
	// MASTER CLUES
	// MASTER CLUES
	double masterCounter = 0, extraMasterCount = 0, eliteCounter = 0, timer = 0;

	int superEnergy = 0, superRestore = 0, superSet = 0, gildedFullHelm = 0,

		robin = 0, plateT = 0, platelegsT = 0, kiteT = 0, fullHelmT = 0, plateG = 0, platelegsG = 0, kiteG = 0, fullHelmG = 0, plateZammy = 0, platelegsZammy = 0, kiteZammy = 0,
		fullHelmZammy = 0, plateSara = 0, platelegsSara = 0, kiteSara = 0, fullHelmSara = 0, plateGuthix = 0, platelegsGuthix = 0, kiteGuthix = 0, fullHelmGuthix = 0, tanCav = 0,
		darkCav = 0, blackCav = 0, pirateHat = 0, plateskirtG = 0, plateskirtT = 0, plateskirtZammy = 0, plateskirtSara = 0, plateskirtGuthix = 0, shieldH1 = 0, shieldH2 = 0, shieldH3 = 0,
		shieldH4 = 0, shieldH5 = 0, blueBodyG = 0, blueBodyT = 0, blueChapsG = 0, blueChapsT = 0, enchantedHat = 0, enchantedTop = 0, enchantedLegs = 0, helm1 = 0, helm2 = 0, helm3 = 0,
		helm4 = 0, helm5 = 0, gloryT = 0, zammyBracers = 0, zammyDBody = 0, zammyChaps = 0, zammyCoif = 0, guthixBracers = 0, guthixDBody = 0, guthixChaps = 0, guthixCoif = 0, saraBracers = 0,
		saraDBody = 0, saraChaps = 0, saraCoif = 0, saraCrozier = 0, guthixCrozier = 0, zammyCrozier = 0, saraStole = 0, guthixStole = 0, zammyStole = 0, redBodyT = 0, redChapsT = 0,
		redBodyG = 0, redChapsG = 0, whiteCav = 0, redCav = 0, navyCav = 0, pithHelm = 0, explorerBackpack = 0, plateBandos = 0, platelegsBandos = 0, plateskirtBandos = 0, fullHelmBandos = 0,
		kiteBandos = 0, plateArmadyl = 0, platelegsArmadyl = 0, plateskirtArmadyl = 0, fullHelmArmadyl = 0, kiteArmadyl = 0, plateAncient = 0, platelegsAncient = 0, plateskirtAncient = 0,
		fullHelmAncient = 0, kiteAncient = 0, ancientBracers = 0, ancientDBody = 0, ancientChaps = 0, ancientCoif = 0, bandosBracers = 0, bandosDBody = 0, bandosChaps = 0,
		bandosCoifs = 0, armadylBracers = 0, armadylDBody = 0, armadylChaps = 0, armadylCoif = 0, greenMask = 0, blueMask = 0, redMask = 0, blackMask = 0, zombieHead = 0, nunchaku = 0,
		cyclopsHead = 0, ancientBoots = 0, bandosBoots = 0, guthixBoots = 0, armadylBoots = 0, saraBoots = 0, zammyBoots = 0, dragonBootsOrn = 0, dualSai = 0, thievingBag = 0,
		runeDefenderKit = 0, tzhaarKit = 0, berserkerKit = 0, runeCane = 0, guthixShield = 0, saraShield = 0, zammyShield = 0, ancientShield = 0, armadylShield = 0, bandosShield = 0,
		plateH1 = 0, plateH2 = 0, plateH3 = 0, plateH4 = 0, plateH5 = 0;

	int nature = 0, crystal = 0, lavaMask = 0, battlestaff = 0, antifire = 0, restore = 0, brew = 0, range = 0, tuxJacket = 0, tuxCuffs = 0, tuxTrousers = 0,
		tuxShoes = 0, tuxBowTie = 0, lightTuxJacket = 0, lightTuxCuffs = 0, lightTuxTrousers = 0, lightTuxShoes = 0, lightTuxBowTie = 0;

	int occultO = 0, tortO = 0, anguishO = 0, tormentedO = 0, defO = 0, darkHood = 0, darkTop = 0, darkGloves = 0, darkBottom = 0, darkBoots = 0, samKasa = 0, samShirt = 0,
		samGloves = 0, samGreaves = 0, samBoots = 0, arcHood = 0, hosHood = 0, lovHood = 0, piscHood = 0, shayHood = 0, oldDemon = 0, lesserDemon = 0, greaterDemon = 0,
		blackDemon = 0, jungleDemon = 0, leftEye = 0, wig = 0, ale = 0, obsidian = 0, fancy = 0, halfMoon = 0, armadylO = 0, bandoO = 0, saraO = 0, zammyO = 0, dragonPlate = 0,
		ankouMask = 0, ankouTop = 0, ankouGloves = 0, ankouLegs = 0, ankouSocks = 0, mummyHead = 0, mummyBody = 0, mummyHands = 0, mummyLegs = 0, mummyFeet = 0, dragonKite = 0,
		thirdHelm = 0, thirdPlate = 0, thirdLegs = 0, thirdSkirt = 0, thirdKite = 0, thirdCoif = 0, thirdRangeTop = 0, thirdRangeLegs = 0, thirdVambs = 0,
		thirdHat = 0, thirdRobeTop = 0, thirdRobeBottom = 0, thirdAmulet = 0, thirdSword = 0, thirdWand = 0, thirdCloak = 0, thirdBow = 0, thirdDruidicStaff = 0, thirdDruidicCloak = 0,
		thirdDruidicTop = 0, thirdDruidicLegs = 0, thirdPick = 0, thirdAxe = 0, pet = 0, gildScim = 0, bucketG = 0, gildBoots = 0, ringCoins = 0, cabbage = 0, antiVenom = 0, torstol = 0,
		gildCoif = 0, gildVamb = 0, gildDTop = 0, gildChaps = 0, gildPick = 0, gildAxe = 0, gildSpade = 0, gildPlate = 0, gildLegs = 0, gildSkirt = 0, gildFullHelm = 0, gildKite = 0,
		gildMed = 0, gildChain = 0, gildSq = 0, gild2h = 0, gildSpear = 0, gildHasta = 0, mimicCount = 0, thirdAgeCount = 0;


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HARD CLUES
// HARD CLUES
// HARD CLUES
// HARD CLUES
//random 4-6 rolls
// 1/15 for master
// 1/13 for rare
// 1/1625 for mega rare(1/125 on rare table)
	double hardCounter = 0;
	//bool trueCheck = false;
	while ( robin == 0 || plateT == 0 || platelegsT == 0 || kiteT == 0 || fullHelmT == 0 || plateG == 0 || platelegsG == 0 || kiteG == 0 || fullHelmG == 0 || plateZammy == 0 || platelegsZammy == 0 || kiteZammy == 0 ||
		fullHelmZammy == 0 || plateSara == 0 || platelegsSara == 0 || kiteSara == 0 || fullHelmSara == 0 || plateGuthix == 0 || platelegsGuthix == 0 || kiteGuthix == 0 || fullHelmGuthix == 0 || tanCav == 0 ||
		darkCav == 0 || blackCav == 0 || pirateHat == 0 || plateskirtG == 0 || plateskirtT == 0 || plateskirtZammy == 0 || plateskirtSara == 0 || plateskirtGuthix == 0 || shieldH1 == 0 || shieldH2 == 0 || shieldH3 == 0 ||
		shieldH4 == 0 || shieldH5 == 0 || blueBodyG == 0 || blueBodyT == 0 || blueChapsG == 0 || blueChapsT == 0 || enchantedHat == 0 || enchantedTop == 0 || enchantedLegs == 0 || helm1 == 0 || helm2 == 0 || helm3 == 0 ||
		helm4 == 0 || helm5 == 0 || gloryT == 0 || zammyBracers == 0 || zammyDBody == 0 || zammyChaps == 0 || zammyCoif == 0 || guthixBracers == 0 || guthixDBody == 0 || guthixChaps == 0 || guthixCoif == 0 || saraBracers == 0 ||
		saraDBody == 0 || saraChaps == 0 || saraCoif == 0 || saraCrozier == 0 || guthixCrozier == 0 || zammyCrozier == 0 || saraStole == 0 || guthixStole == 0 || zammyStole == 0 || redBodyT == 0 || redChapsT == 0 ||
		redBodyG == 0 || redChapsG == 0 || whiteCav == 0 || redCav == 0 || navyCav == 0 || pithHelm == 0 || explorerBackpack == 0 || plateBandos == 0 || platelegsBandos == 0 || plateskirtBandos == 0 || fullHelmBandos == 0 ||
		kiteBandos == 0 || plateArmadyl == 0 || platelegsArmadyl == 0 || plateskirtArmadyl == 0 || fullHelmArmadyl == 0 || kiteArmadyl == 0 || plateAncient == 0 || platelegsAncient == 0 || plateskirtAncient == 0 ||
		fullHelmAncient == 0 || kiteAncient == 0 || ancientBracers == 0 || ancientDBody == 0 || ancientChaps == 0 || ancientCoif == 0 || bandosBracers == 0 || bandosDBody == 0 || bandosChaps == 0 ||
		bandosCoifs == 0 || armadylBracers == 0 || armadylDBody == 0 || armadylChaps == 0 || armadylCoif == 0 || greenMask == 0 || blueMask == 0 || redMask == 0 || blackMask == 0 || zombieHead == 0 || nunchaku == 0 ||
		cyclopsHead == 0 || ancientBoots == 0 || bandosBoots == 0 || guthixBoots == 0 || armadylBoots == 0 || saraBoots == 0 || zammyBoots == 0 || dragonBootsOrn == 0 || dualSai == 0 || thievingBag == 0 ||
		runeDefenderKit == 0 || tzhaarKit == 0 || berserkerKit == 0 || runeCane == 0 || guthixShield == 0 || saraShield == 0 || zammyShield == 0 || ancientShield == 0 || armadylShield == 0 || bandosShield == 0 || plateH1 == 0 || plateH2 == 0 ||
		plateH3 == 0 || plateH4 == 0 || plateH5 == 0 || 
		
		thirdPlate == 0 || thirdHelm == 0 || thirdLegs == 0 || thirdSkirt == 0 || thirdKite == 0 || thirdAmulet == 0 ||
		thirdRobeBottom == 0 || thirdRobeTop == 0 || thirdHat == 0 || thirdRangeLegs == 0 || thirdRangeTop == 0 || thirdCoif == 0 || thirdVambs == 0 /*trueCheck == false*/)
	{
		int hardRolls = rand() % 3 + 4;
		for (int i = 0; i < hardRolls; i++)
		{
			int initialTable = rand() % 13 + 1;
			if (initialTable == 1) // hit rare table
			{
				int rareTable = rand() % 125 + 1;
				switch (rareTable)
				{
				case 1:
						robin++;
						break;
				case 2:
						plateT++;
						break;
					case 3:
						platelegsT++;
						break;
					case 4:
						kiteT++;
						break;
					case 5:
						fullHelmT++;
						break;
					case 6:
						plateG++;
						break;
					case 7:
						platelegsG++;
						break;
					case 8:
						kiteG++;
						break;
					case 9:
						fullHelmG++;
						break;
					case 10:
						plateZammy++;
						break;
					case 11:
						platelegsZammy++;
						break;
					case 12:
						kiteZammy++;
						break;
					case 13:
						fullHelmZammy++;
						break;
					case 14:
						plateSara++;
						break;
					case 15:
						platelegsSara++;
						break;
					case 16:
						kiteSara++;
						break;
					case 17:
						fullHelmSara++;
						break;
					case 18:
						plateGuthix++;
						break;
					case 19:
						platelegsGuthix++;
						break;
					case 20:
						kiteGuthix++;
						break;
					case 21:
						fullHelmGuthix++;
						break;
					case 22:
						tanCav++;
						break;
					case 23:
						darkCav++;
						break;
					case 24:
						blackCav++;
						break;
					case 25:
						pirateHat++;
						break;
					case 26:
						plateskirtG++;
						break;
					case 27:
						plateskirtT++;
						break;
					case 28:
						plateskirtZammy++;
						break;
					case 29:
						plateskirtSara++;
						break;
					case 30:
						plateskirtGuthix++;
						break;
					case 31:
						shieldH1++;
						break;
					case 32:
						shieldH2++;
						break;
					case 33:
						shieldH3++;
						break;
					case 34:
						shieldH4++;
						break;
					case 35:
						shieldH5++;
						break;
					case 36:
						blueBodyG++;
						break;
					case 37:
						blueBodyT++;
						break;
					case 38:
						blueChapsG++;
						break;
					case 39:
						blueChapsT++;
						break;
					case 40:
						enchantedHat++;
						break;
					case 41:
						enchantedTop++;
						break;
					case 42:
						enchantedLegs++;
						break;
					case 43:
						helm1++;
						break;
					case 44:
						helm2++;
						break;
					case 45:
						helm3++;
						break;
					case 46:
						helm4++;
						break;
					case 47:
						helm5++;
						break;
					case 48:
						gloryT++;
						break;
					case 49:
						zammyBracers++;
						break;
					case 50:
						zammyDBody++;
						break;
					case 51:
						zammyChaps++;
						break;
					case 52:
						zammyCoif++;
						break;
					case 53:
						guthixBracers++;
						break;
					case 54:
						guthixDBody++;
						break;
					case 55:
						guthixChaps++;
						break;
					case 56:
						guthixCoif++;
						break;
					case 57:
						saraBracers++;
						break;
					case 58:
						saraDBody++;
						break;
					case 59:
						saraChaps++;
						break;
					case 60:
						saraCoif++;
						break;
					case 61:
						saraCrozier++;
						break;
					case 62:
						guthixCrozier++;
						break;
					case 63:
						zammyCrozier++;
						break;
					case 64:
						saraStole++;
						break;
					case 65:
						guthixStole++;
						break;
					case 66:
						zammyStole++;
						break;
					case 67:
						redBodyT++;
						break;
					case 68:
						redChapsT++;
						break;
					case 69:
						redBodyG++;
						break;
					case 70:
						redChapsG++;
						break;
					case 71:
						whiteCav++;
						break;
					case 72:
						redCav++;
						break;
					case 73:
						navyCav++;
						break;
					case 74:
						pithHelm++;
						break;
					case 75:
						explorerBackpack++;
						break;
					case 76:
						plateBandos++;
						break;
					case 77:
						platelegsBandos++;
						break;
					case 78:
						plateskirtBandos++;
						break;
					case 79:
						fullHelmBandos++;
						break;
					case 80:
						kiteBandos++;
						break;
					case 81:
						plateArmadyl++;
						break;
					case 82:
						platelegsArmadyl++;
						break;
					case 83:
						plateskirtArmadyl++;
						break;
					case 84:
						fullHelmArmadyl++;
						break;
					case 85:
						kiteArmadyl++;
						break;
					case 86:
						plateAncient++;
						break;
					case 87:
						platelegsAncient++;
						break;
					case 88:
						plateskirtAncient++;
						break;
					case 89:
						fullHelmAncient++;
						break;
					case 90:
						kiteAncient++;
						break;
					case 91:
						ancientBracers++;
						break;
					case 92:
						ancientDBody++;
						break;
					case 93:
						ancientChaps++;
						break;
					case 94:
						ancientCoif++;
						break;
					case 95:
						bandosBracers++;
						break;
					case 96:
						bandosDBody++;
						break;
					case 97:
						bandosChaps++;
						break;
					case 98:
						bandosCoifs++;
						break;
					case 99:
						armadylBracers++;
						break;
					case 100:
						armadylDBody++;
						break;
					case 101:
						armadylChaps++;
						break;
					case 102:
						armadylCoif++;
						break;
					case 103:
						greenMask++;
						break;
					case 104:
						blueMask++;
						break;
					case 105:
						redMask++;
						break;
					case 106:
						blackMask++;
						break;
					case 107:
						zombieHead++;
						break;
					case 108:
						nunchaku++;
						break;
					case 109:
						cyclopsHead++;
						break;
					case 110:
						ancientBoots++;
						break;
					case 111:
						bandosBoots++;
						break;
					case 112:
						guthixBoots++;
						break;
					case 113:
						armadylBoots++;
						break;
					case 114:
						saraBoots++;
						break;
					case 115:
						zammyBoots++;
						break;
					case 116:
						dragonBootsOrn++;
						break;
					case 117:
						dualSai++;
						break;
					case 118:
						thievingBag++;
						break;
					case 119:
						runeDefenderKit++;
						break;
					case 120:
						tzhaarKit++;
						break;
					case 121:
						berserkerKit++;
						break;
					case 122:
						runeCane++;
						break;
				}
				if (rareTable == 123)
				{
					int shieldRoll = rand() % 6 + 1;
					switch (shieldRoll)
					{
					case 1: guthixShield++;
						break;
					case 2: saraShield++;
						break;
					case 3: zammyShield++;
						break;
					case 4: ancientShield++;
						break;
					case 5: armadylShield++;
						break;
					case 6: bandosShield++;
						break;
					}
				}
				else if (rareTable == 124)
				{
					int heraldicRoll = rand() % 5 + 1;
					switch (heraldicRoll)
					{
					case 1: plateH1++;
						break;
					case 2: plateH2++;
						break;
					case 3: plateH3++;
						break;
					case 4: plateH4++;
						break;
					case 5: plateH5++;
						break;
					}
				}
				else if (rareTable == 125) // hit mega rare table
				{
					int megaRareTable = rand() % 10 + 1;
					if (megaRareTable == 1)
						superEnergy += 15;
					else if (megaRareTable == 2)
						superRestore += 15;
					else if (megaRareTable == 3)
						antifire += 15;
					else if (megaRareTable == 4)
						superSet += 15;
					else if (megaRareTable == 5)
					{
						int thirdAgeRoll = rand() % 13 + 1;
						if (thirdAgeRoll == 1)
							thirdHelm++;
						else if (thirdAgeRoll == 2)
							thirdPlate++;
						else if (thirdAgeRoll == 3)
							thirdLegs++;
						else if (thirdAgeRoll == 4)
							thirdSkirt++;
						else if (thirdAgeRoll == 5)
							thirdKite++;
						else if (thirdAgeRoll == 6)
							thirdCoif++;
						else if (thirdAgeRoll == 7)
							thirdRangeTop++;
						else if (thirdAgeRoll == 8)
							thirdRangeLegs++;
						else if (thirdAgeRoll == 9)
							thirdVambs++;
						else if (thirdAgeRoll == 10)
							thirdHat++;
						else if (thirdAgeRoll == 11)
							thirdRobeTop++;
						else if (thirdAgeRoll == 12)
							thirdRobeBottom++;
						else if (thirdAgeRoll == 13)
							thirdAmulet++;
					}
					else if (5 < megaRareTable < 11)
					{
						int gildRoll = rand() % 11 + 1;
						if (gildRoll == 1)
							gildFullHelm++;
						else if (gildRoll == 2)
							gildPlate++;
						else if (gildRoll == 3)
							gildLegs++;
						else if (gildRoll == 4)
							gildSkirt++;
						else if (gildRoll == 5)
							gildKite++;
						else if (gildRoll == 6)
							gildMed++;
						else if (gildRoll == 7)
							gildChain++;
						else if (gildRoll == 8)
							gildSq++;
						else if (gildRoll == 9)
							gild2h++;
						else if (gildRoll == 10)
							gildSpear++;
						else if (gildRoll == 11)
							gildHasta++;
					}
				}
			}
		}
		int master = rand() % 15 + 1;
		if (master == 1)
			extraMasterCount++;
		hardCounter++;
		timer += 6;

		//if (extraMasterCount > 0)
		//{
		//	int mimicRoll = rand() % 15 + 1;
		//	if (mimicRoll == 15)
		//	{
		//		int rareMimicRoll = rand() % 228 + 1;
		//		if (rareMimicRoll == 228)
		//		{
		//			int mimicThirdRoll = rand() % 23 + 1;
		//			if (mimicThirdRoll == 1)
		//				thirdCoif++;
		//			else if (mimicThirdRoll == 2)
		//				thirdRangeTop++;
		//			else if (mimicThirdRoll == 3)
		//				thirdRangeLegs++;
		//			else if (mimicThirdRoll == 4)
		//				thirdVambs++;
		//			else if (mimicThirdRoll == 5)
		//				thirdRobeTop++;
		//			else if (mimicThirdRoll == 6)
		//				thirdRobeBottom++;
		//			else if (mimicThirdRoll == 7)
		//				thirdHat++;
		//			else if (mimicThirdRoll == 8)
		//				thirdAmulet++;
		//			else if (mimicThirdRoll == 9)
		//				thirdLegs++;
		//			else if (mimicThirdRoll == 10)
		//				thirdPlate++;
		//			else if (mimicThirdRoll == 11)
		//				thirdHelm++;
		//			else if (mimicThirdRoll == 12)
		//				thirdSkirt++;
		//			else if (mimicThirdRoll == 13)
		//				thirdKite++;
		//			else if (mimicThirdRoll == 14)
		//				thirdSword++;
		//			else if (mimicThirdRoll == 15)
		//				thirdCloak++;
		//			else if (mimicThirdRoll == 16)
		//				thirdWand++;
		//			else if (mimicThirdRoll == 17)
		//				thirdBow++;
		//			else if (mimicThirdRoll == 18)
		//				thirdDruidicStaff++;
		//			else if (mimicThirdRoll == 19)
		//				thirdDruidicCloak++;
		//			else if (mimicThirdRoll == 20)
		//				thirdDruidicLegs++;
		//			else if (mimicThirdRoll == 21)
		//				thirdDruidicTop++;
		//			else if (mimicThirdRoll == 22)
		//				thirdPick++;
		//			else if (mimicThirdRoll == 23)
		//				thirdAxe++;
		//		}
		//	}
		//	extraMasterCount--;
		//}

		//if (thirdPlate != 0 && (thirdLegs != 0 || thirdSkirt != 0) && thirdHelm != 0 && thirdKite != 0)
		//	trueCheck = true;

		//if (thirdRobeBottom != 0 && thirdRobeTop != 0 && thirdAmulet != 0 && thirdHat != 0)
		//	trueCheck = true;

		//if (thirdRangeLegs != 0 && thirdRangeTop != 0 && thirdCoif != 0 && thirdVambs != 0)
		//	trueCheck = true;
	}
	if (option == 1)
	{
		std::cout << "Total hard clues completed: " << hardCounter << '\n';
		std::cout << "Total masters: " << extraMasterCount << '\n';
		std::cout << "3rd Age Platebodies: " << thirdPlate << '\n';
		std::cout << "3rd Age Platelegs: " << thirdLegs << '\n';
		std::cout << "3rd Age Full Helms: " << thirdHelm << '\n';
		std::cout << "3rd Age KiteShields: " << thirdKite << '\n';
		std::cout << "3rd Age Plateskirts: " << thirdSkirt << '\n';
		std::cout << "3rd Age Robetop: " << thirdRobeTop << '\n';
		std::cout << "3rd Age Robebottom: " << thirdRobeBottom << '\n';
		std::cout << "3rd Age Mage Hat: " << thirdHat << '\n';
		std::cout << "3rd Age Amulet: " << thirdAmulet << '\n';
		std::cout << "3rd Age Coif: " << thirdCoif << '\n';
		std::cout << "3rd Age Range Top: " << thirdRangeTop << '\n';
		std::cout << "3rd Age Range Legs: " << thirdRangeLegs << '\n';
		std::cout << "3rd Age Vambs: " << thirdVambs << '\n';
		std::cout << "Super Sets: " << superSet << '\n';
		std::cout << "Super energies: " << superEnergy << '\n';
		std::cout << "Super restores: " << superRestore << '\n';
		std::cout << "Antifires: " << antifire << '\n';
		std::cout << "Gilded Platebodies: " << gildPlate << '\n';
		std::cout << "Gilded Platelegs: " << gildLegs << '\n';
		std::cout << "Gilded full helm: " << gildFullHelm << '\n';
		std::cout << "Gilded kiteshield: " << gildKite << '\n';
		std::cout << "Gilded plateskirt: " << gildSkirt << '\n';
		std::cout << "Gilded med helm: " << gildMed << '\n';
		std::cout << "Gilded chainbody: " << gildChain << '\n';
		std::cout << "Gilded square shield: " << gildSq << '\n';
		std::cout << "Gilded 2h: " << gild2h << '\n';
		std::cout << "Gilded spear: " << gildSpear << '\n';
		std::cout << "Gilded hasta: " << gildHasta << '\n';
		std::cout << "Bandos shield: " << bandosShield << '\n';
		std::cout << "Arma shield: " << armadylShield << '\n';
		std::cout << "Ancient shield: " << ancientShield << '\n';
		std::cout << "Zammy shield: " << zammyShield << '\n';
		std::cout << "Sara shield: " << saraShield << '\n';
		std::cout << "Guthix shield: " << guthixShield << '\n';
		std::cout << "Total Time spent: " << timer / 60 << '\n';
		std::cout << "First hard cycle finished\n\n\n";
	}

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ELITE CLUES
	// ELITE CLUES
	// ELITE CLUES
	// ELITE CLUES
 
	double gpReserve = 0;

	while (nature == 0 || lavaMask == 0 || tuxJacket == 0 || tuxCuffs == 0 || tuxTrousers == 0 || tuxShoes == 0 || tuxBowTie == 0 || lightTuxJacket == 0 || lightTuxCuffs == 0 || lightTuxTrousers == 0 || lightTuxShoes == 0 ||
		lightTuxBowTie == 0)
	{
		if (gpReserve > 7045548)
		{
			gpReserve -= 7045548; // Bought dragon imps for this elite, then loot from elite is 243542
			gpReserve += 243542;
			timer += 10;
		}
		else
		{
			gpReserve += 1963402;		// 60 sarachnis kills gp to get elite clue, 60 kills/hr and 1719860 gp per 60 kills + 243542 from elite, 10 minutes to do the elite itself
			timer += 70;				// You've gotten your elite and now go through the table
		}

		for (int i = 0; i < 5; i++)
		{
			int roll = rand() % 25 + 1;
			if (roll == 25)
			{
				int rareRoll = rand() % 50 + 1;
				if (rareRoll == 49)
				{
					int tuxRoll = rand() % 10 + 1;
					switch (tuxRoll)
					{
					case 1: tuxJacket++;
						break;
					case 2: tuxCuffs++;
						break;
					case 3: tuxTrousers++;
						break;
					case 4: tuxShoes++;
						break;
					case 5: tuxBowTie++;
						break;
					case 6: lightTuxJacket++;
						break;
					case 7: lightTuxCuffs++;
						break;
					case 8: lightTuxTrousers++;
						break;
					case 9: lightTuxShoes++;
						break;
					case 10: lightTuxBowTie++;
						break;
					}
				}
				if (rareRoll == 50)
				{
					int megaRoll = rand() % 23 + 1;
					if (megaRoll == 1)
						nature++;
					else if (megaRoll == 2)
						crystal++;
					else if (megaRoll == 3)
						lavaMask++;
					else if (megaRoll == 4)
						battlestaff++;
					else if (megaRoll == 5)
						antifire++;
					else if (megaRoll == 6)
						restore++;
					else if (megaRoll == 7)
						brew++;
					else if (megaRoll == 8)
						range++;
					else if (megaRoll == 9)
						gildScim++;
					else if (megaRoll == 10)
						gildBoots++;
					else if (megaRoll == 11)
						gildCoif++;
					else if (megaRoll == 12)
						gildDTop++;
					else if (megaRoll == 13)
						gildChaps++;
					else if (megaRoll == 14)
						gildPick++;
					else if (megaRoll == 15)
						gildAxe++;
					else if (megaRoll == 16)
						gildSpade++;
					else if (megaRoll > 16 && megaRoll < 22)
					{
						int gildRoll = rand() % 11 + 1;
						if (gildRoll == 1)
							gildPlate++;
						else if (gildRoll == 2)
							gildFullHelm++;
						else if (gildRoll == 3)
							gildLegs++;
						else if (gildRoll == 4)
							gildSkirt++;
						else if (gildRoll == 5)
							gildKite++;
						else if (gildRoll == 6)
							gildMed++;
						else if (gildRoll == 7)
							gildChain++;
						else if (gildRoll == 8)
							gildSq++;
						else if (gildRoll == 9)
							gild2h++;
						else if (gildRoll == 10)
							gildSpear++;
						else if (gildRoll == 11)
							gildHasta++;
					}
					else if (megaRoll == 22)
						gildVamb++;
					else if (megaRoll == 23)
					{
						int thirdRoll = rand() % 17 + 1;
						if (thirdRoll == 1)
							thirdCoif++;
						else if (thirdRoll == 2)
							thirdRangeTop++;
						else if (thirdRoll == 3)
							thirdRangeLegs++;
						else if (thirdRoll == 4)
							thirdVambs++;
						else if (thirdRoll == 5)
							thirdRobeTop++;
						else if (thirdRoll == 6)
							thirdRobeBottom++;
						else if (thirdRoll == 7)
							thirdHat++;
						else if (thirdRoll == 8)
							thirdAmulet++;
						else if (thirdRoll == 9)
							thirdPlate++;
						else if (thirdRoll == 10)
							thirdLegs++;
						else if (thirdRoll == 11)
							thirdHelm++;
						else if (thirdRoll == 12)
							thirdKite++;
						else if (thirdRoll == 13)
							thirdSkirt++;
						else if (thirdRoll == 14)
							thirdSword++;
						else if (thirdRoll == 15)
							thirdWand++;
						else if (thirdRoll == 16)
							thirdCloak++;
						else if (thirdRoll == 17)
							thirdBow++;
					}
				}
			}
		}
		int mimicRoll = rand() % 35 + 1;
		if (mimicRoll == 35)
		{
			int rareMimicRoll = rand() % 250 + 1;
			if (rareMimicRoll == 250)
			{
				int mimicThirdRoll = rand() % 23 + 1;
				if (mimicThirdRoll == 1)
					thirdCoif++;
				else if (mimicThirdRoll == 2)
					thirdRangeTop++;
				else if (mimicThirdRoll == 3)
					thirdRangeLegs++;
				else if (mimicThirdRoll == 4)
					thirdVambs++;
				else if (mimicThirdRoll == 5)
					thirdRobeTop++;
				else if (mimicThirdRoll == 6)
					thirdRobeBottom++;
				else if (mimicThirdRoll == 7)
					thirdHat++;
				else if (mimicThirdRoll == 8)
					thirdAmulet++;
				else if (mimicThirdRoll == 9)
					thirdLegs++;
				else if (mimicThirdRoll == 10)
					thirdPlate++;
				else if (mimicThirdRoll == 11)
					thirdHelm++;
				else if (mimicThirdRoll == 12)
					thirdSkirt++;
				else if (mimicThirdRoll == 13)
					thirdKite++;
				else if (mimicThirdRoll == 14)
					thirdSword++;
				else if (mimicThirdRoll == 15)
					thirdCloak++;
				else if (mimicThirdRoll == 16)
					thirdWand++;
				else if (mimicThirdRoll == 17)
					thirdBow++;
				else if (mimicThirdRoll == 18)
					thirdDruidicStaff++;
				else if (mimicThirdRoll == 19)
					thirdDruidicCloak++;
				else if (mimicThirdRoll == 20)
					thirdDruidicLegs++;
				else if (mimicThirdRoll == 21)
					thirdDruidicTop++;
				else if (mimicThirdRoll == 22)
					thirdPick++;
				else if (mimicThirdRoll == 23)
					thirdAxe++;
			}
		}
		int master = rand() % 5 + 1;
		if (master == 1)
			extraMasterCount++;
		eliteCounter++;
	}
	if (option == 1)
	{
		std::cout << "Total ring of natures: " << nature << '\n';
		std::cout << "Total lava dragon masks: " << lavaMask << '\n';
		std::cout << "Total dark tux jackets: " << tuxJacket << '\n';
		std::cout << "Total dark tux trousers: " << tuxTrousers << '\n';
		std::cout << "Total light tux jackets: " << lightTuxJacket << '\n';
		std::cout << "Total light tux trousers: " << lightTuxTrousers << '\n';
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total elite clues completed: " << eliteCounter << '\n';
		std::cout << "Total Time spent: " << timer / 60 << '\n';
		std::cout << "First elite cycle finished\n\n\n";
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// MASTER CLUES
		// MASTER CLUES
		// MASTER CLUES
		// MASTER CLUES
		// MASTER CLUES
		// MASTER CLUES

	while (occultO == 0 || tortO == 0 || anguishO == 0 || tormentedO == 0 || defO == 0 || darkHood == 0 || darkTop == 0 || darkGloves == 0 || darkBottom == 0 || darkBoots == 0 || samKasa == 0 ||
		samShirt == 0 || samGloves == 0 || samGreaves == 0 || samBoots == 0 || arcHood == 0 || hosHood == 0 || lovHood == 0 || piscHood == 0 || shayHood == 0 || oldDemon == 0 || lesserDemon == 0 ||
		greaterDemon == 0 || blackDemon == 0 || jungleDemon == 0 || leftEye == 0 || wig == 0 || ale == 0 || obsidian == 0 || fancy == 0 || halfMoon == 0 || armadylO == 0 || bandoO == 0 ||
		saraO == 0 || zammyO == 0 || dragonPlate == 0 || ankouMask == 0 || ankouTop == 0 || ankouGloves == 0 || ankouLegs == 0 || ankouSocks == 0 || mummyHead == 0 || mummyBody == 0 ||
		mummyHands == 0 || mummyLegs == 0 || mummyFeet == 0 || dragonKite == 0 || ringCoins == 0 || bucketG == 0 || gildCoif == 0 || gildScim == 0 || gildBoots == 0 || gildVamb == 0 ||
		gildDTop == 0 || gildChaps == 0 || gildAxe == 0 || gildPick == 0 || gildSpade == 0 || pet == 0 || thirdDruidicStaff == 0 || thirdDruidicCloak == 0 ||
		thirdDruidicTop == 0 || thirdDruidicLegs == 0 || thirdPick == 0 || thirdAxe == 0 || thirdSword == 0 || thirdWand == 0 || thirdCloak == 0 || thirdBow == 0)
	{
		if (extraMasterCount > 0)
		{
			extraMasterCount--;
			timer += 15;
		}
		else if (gpReserve >= 7045548)
		{
			gpReserve -= 7045548; // Bought dragon imps for this elite, then loot from elite is 243542
			gpReserve += 803273;
			timer += 15;
		}
		else if (gpReserve < 7045548)
		{
			gpReserve += 2523133;		// 60 sarachnis kills gp to get elite clue, 60 kills/hr and 1719860 gp per 60 kills + 243542 from elite, 10 minutes to do the elite itself
			timer += 75;				// You've gotten your elite and now go through the table
		}

		for (int i = 0; i < 6; i++)
		{
			int roll = rand() % 23 + 1;
			if (roll == 23)
			{
				int rareRoll = rand() % 37 + 1;
				switch (rareRoll)
				{
				case 1: leftEye++;
					break;
				case 2: wig++;
					break;
				case 3: ale++;
					break;
				case 4: halfMoon++;
					break;
				case 5: fancy++;
					break;
				case 6: darkHood++;
					break;
				case 7: darkTop++;
					break;
				case 8: darkBottom++;
					break;
				case 9: darkBoots++;
					break;
				case 10: darkGloves++;
					break;
				case 11: obsidian++;
					break;
				case 12: occultO++;
					break;
				case 13: tortO++;
					break;
				case 14: defO++;
					break;
				case 15: samKasa++;
					break;
				case 16: samShirt++;
					break;
				case 17: samGreaves++;
					break;
				case 18: samBoots++;
					break;
				case 19: samGloves++;
					break;
				case 20: arcHood++;
					break;
				case 21: hosHood++;
					break;
				case 22: lovHood++;
					break;
				case 23: piscHood++;
					break;
				case 24: shayHood++;
					break;
				case 25: lesserDemon++;
					break;
				case 26: greaterDemon++;
					break;
				case 27: blackDemon++;
					break;
				case 28: jungleDemon++;
					break;
				case 29: oldDemon++;
					break;
				case 30: anguishO++;
					break;
				case 31: tormentedO++;
					break;
				case 32:
				{
					int megaRoll = rand() % 16 + 1;
					switch (megaRoll)
					{
					case 1: gildScim++;
						break;
					case 2: bucketG++;
						break;
					case 3: gildBoots++;
						break;
					case 4: ringCoins++;
						break;
					case 5: cabbage++;
						break;
					case 6: antiVenom++;
						break;
					case 7: torstol++;
						break;
					case 8: gildCoif++;
						break;
					case 9: gildVamb++;
						break;
					case 10: gildDTop++;
						break;
					case 11: gildChaps++;
						break;
					case 12: gildPick++;
						break;
					case 13: gildAxe++;
						break;
					case 14: gildSpade++;
						break;
					case 15:
					{
						int gildRoll = rand() % 11 + 1;
						switch (gildRoll)
						{
						case 1: gildPlate++;
							break;
						case 2: gildLegs++;
							break;
						case 3: gildSkirt++;
							break;
						case 4: gildFullHelm++;
							break;
						case 5: gildKite++;
							break;
						case 6: gildMed++;
							break;
						case 7: gildChain++;
							break;
						case 8: gildSq++;
							break;
						case 9: gild2h++;
							break;
						case 10: gildSpear++;
							break;
						case 11: gildHasta++;
							break;
						}
					}
					break;
					}
					if (megaRoll == 16)
					{
						int thirdTable = rand() % 23 + 1;
						if (thirdTable == 1)
							thirdCoif++;
						else if (thirdTable == 2)
							thirdRangeTop++;
						else if (thirdTable == 3)
							thirdRangeLegs++;
						else if (thirdTable == 4)
							thirdVambs++;
						else if (thirdTable == 5)
							thirdRobeTop++;
						else if (thirdTable == 6)
							thirdRobeBottom++;
						else if (thirdTable == 7)
							thirdHat++;
						else if (thirdTable == 8)
							thirdAmulet++;
						else if (thirdTable == 9)
							thirdLegs++;
						else if (thirdTable == 10)
							thirdPlate++;
						else if (thirdTable == 11)
							thirdHelm++;
						else if (thirdTable == 12)
							thirdSkirt++;
						else if (thirdTable == 13)
							thirdKite++;
						else if (thirdTable == 14)
							thirdSword++;
						else if (thirdTable == 15)
							thirdCloak++;
						else if (thirdTable == 16)
							thirdWand++;
						else if (thirdTable == 17)
							thirdBow++;
						else if (thirdTable == 18)
							thirdDruidicStaff++;
						else if (thirdTable == 19)
							thirdDruidicCloak++;
						else if (thirdTable == 20)
							thirdDruidicLegs++;
						else if (thirdTable == 21)
							thirdDruidicTop++;
						else if (thirdTable == 22)
							thirdPick++;
						else if (thirdTable == 23)
							thirdAxe++;
					}
				}
				case 33:
					break;
				case 34:
				{
					int godRoll = rand() % 4 + 1;
					if (godRoll == 1)
						armadylO++;
					else if (godRoll == 2)
						bandoO++;
					else if (godRoll == 3)
						zammyO++;
					else if (godRoll == 4)
						saraO++;
				}
				break;
				case 35:
				{
					int ankouRoll = rand() % 5 + 1;
					if (ankouRoll == 1)
						ankouMask++;
					else if (ankouRoll == 2)
						ankouTop++;
					else if (ankouRoll == 3)
						ankouLegs++;
					else if (ankouRoll == 4)
						ankouGloves++;
					else if (ankouRoll == 5)
						ankouSocks++;
				}
				break;
				case 36:
				{
					int mummyRoll = rand() % 5 + 1;
					if (mummyRoll == 1)
						mummyHead++;
					else if (mummyRoll == 2)
						mummyBody++;
					else if (mummyRoll == 3)
						mummyLegs++;
					else if (mummyRoll == 4)
						mummyFeet++;
					else if (mummyRoll == 5)
						mummyHands++;
				}
				break;
				case 37:
				{
					int coinRoll = rand() % 10 + 1;
					if (coinRoll == 10)
					{
						int dragonRoll = rand() % 3 + 1;
						if (dragonRoll == 1)
							dragonKite++;
						else
							dragonPlate++;
					}
				}
				break;
				}
			}
		}

		int mimicRoll = rand() % 15 + 1;
		if (mimicRoll == 15)
		{
			int rareMimicRoll = rand() % 228 + 1;
			if (rareMimicRoll == 228)
			{
				int mimicThirdRoll = rand() % 23 + 1;
				if (mimicThirdRoll == 1)
					thirdCoif++;
				else if (mimicThirdRoll == 2)
					thirdRangeTop++;
				else if (mimicThirdRoll == 3)
					thirdRangeLegs++;
				else if (mimicThirdRoll == 4)
					thirdVambs++;
				else if (mimicThirdRoll == 5)
					thirdRobeTop++;
				else if (mimicThirdRoll == 6)
					thirdRobeBottom++;
				else if (mimicThirdRoll == 7)
					thirdHat++;
				else if (mimicThirdRoll == 8)
					thirdAmulet++;
				else if (mimicThirdRoll == 9)
					thirdLegs++;
				else if (mimicThirdRoll == 10)
					thirdPlate++;
				else if (mimicThirdRoll == 11)
					thirdHelm++;
				else if (mimicThirdRoll == 12)
					thirdSkirt++;
				else if (mimicThirdRoll == 13)
					thirdKite++;
				else if (mimicThirdRoll == 14)
					thirdSword++;
				else if (mimicThirdRoll == 15)
					thirdCloak++;
				else if (mimicThirdRoll == 16)
					thirdWand++;
				else if (mimicThirdRoll == 17)
					thirdBow++;
				else if (mimicThirdRoll == 18)
					thirdDruidicStaff++;
				else if (mimicThirdRoll == 19)
					thirdDruidicCloak++;
				else if (mimicThirdRoll == 20)
					thirdDruidicLegs++;
				else if (mimicThirdRoll == 21)
					thirdDruidicTop++;
				else if (mimicThirdRoll == 22)
					thirdPick++;
				else if (mimicThirdRoll == 23)
					thirdAxe++;
			}
		}
		int petRoll = rand() % 1000 + 1;
		if (petRoll == 1)
			pet++;
		masterCounter++;
	}
	if (option == 1)
	{
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total 3rd age picks: " << thirdPick << '\n';
		std::cout << "Total 3rd age axe: " << thirdAxe << '\n';
		std::cout << "Total druidic tops: " << thirdDruidicTop << '\n';
		std::cout << "Total druidic legs: " << thirdDruidicLegs << '\n';
		std::cout << "Total druidic staff: " << thirdDruidicStaff << '\n';
		std::cout << "Total druidic cloaks: " << thirdDruidicCloak << '\n';
		std::cout << "Total master clues completed: " << masterCounter << '\n';
		std::cout << "Total Time spent: " << timer / 60 << '\n';
		std::cout << "First master cycle finished\n\n\n";
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HARD CLUES
// HARD CLUES
// HARD CLUES
// HARD CLUES

	while (gildPlate == 0 || gildLegs == 0 || gildSkirt == 0 || gildFullHelm == 0 || gildKite == 0 ||
		gildMed == 0 || gildChain == 0 || gildSq == 0 || gild2h == 0 || gildSpear == 0 || gildHasta == 0)
	{
		timer += 6;

		int hardRolls = rand() % 3 + 4;
		for (int i = 0; i < hardRolls; i++)
		{
			int initialTable = rand() % 13 + 1;
			if (initialTable == 1) // hit rare table
			{
				int rareTable = rand() % 125 + 1;
				switch (rareTable)
				{
				case 1:
					robin++;
					break;
				case 2:
					plateT++;
					break;
				case 3:
					platelegsT++;
					break;
				case 4:
					kiteT++;
					break;
				case 5:
					fullHelmT++;
					break;
				case 6:
					plateG++;
					break;
				case 7:
					platelegsG++;
					break;
				case 8:
					kiteG++;
					break;
				case 9:
					fullHelmG++;
					break;
				case 10:
					plateZammy++;
					break;
				case 11:
					platelegsZammy++;
					break;
				case 12:
					kiteZammy++;
					break;
				case 13:
					fullHelmZammy++;
					break;
				case 14:
					plateSara++;
					break;
				case 15:
					platelegsSara++;
					break;
				case 16:
					kiteSara++;
					break;
				case 17:
					fullHelmSara++;
					break;
				case 18:
					plateGuthix++;
					break;
				case 19:
					platelegsGuthix++;
					break;
				case 20:
					kiteGuthix++;
					break;
				case 21:
					fullHelmGuthix++;
					break;
				case 22:
					tanCav++;
					break;
				case 23:
					darkCav++;
					break;
				case 24:
					blackCav++;
					break;
				case 25:
					pirateHat++;
					break;
				case 26:
					plateskirtG++;
					break;
				case 27:
					plateskirtT++;
					break;
				case 28:
					plateskirtZammy++;
					break;
				case 29:
					plateskirtSara++;
					break;
				case 30:
					plateskirtGuthix++;
					break;
				case 31:
					shieldH1++;
					break;
				case 32:
					shieldH2++;
					break;
				case 33:
					shieldH3++;
					break;
				case 34:
					shieldH4++;
					break;
				case 35:
					shieldH5++;
					break;
				case 36:
					blueBodyG++;
					break;
				case 37:
					blueBodyT++;
					break;
				case 38:
					blueChapsG++;
					break;
				case 39:
					blueChapsT++;
					break;
				case 40:
					enchantedHat++;
					break;
				case 41:
					enchantedTop++;
					break;
				case 42:
					enchantedLegs++;
					break;
				case 43:
					helm1++;
					break;
				case 44:
					helm2++;
					break;
				case 45:
					helm3++;
					break;
				case 46:
					helm4++;
					break;
				case 47:
					helm5++;
					break;
				case 48:
					gloryT++;
					break;
				case 49:
					zammyBracers++;
					break;
				case 50:
					zammyDBody++;
					break;
				case 51:
					zammyChaps++;
					break;
				case 52:
					zammyCoif++;
					break;
				case 53:
					guthixBracers++;
					break;
				case 54:
					guthixDBody++;
					break;
				case 55:
					guthixChaps++;
					break;
				case 56:
					guthixCoif++;
					break;
				case 57:
					saraBracers++;
					break;
				case 58:
					saraDBody++;
					break;
				case 59:
					saraChaps++;
					break;
				case 60:
					saraCoif++;
					break;
				case 61:
					saraCrozier++;
					break;
				case 62:
					guthixCrozier++;
					break;
				case 63:
					zammyCrozier++;
					break;
				case 64:
					saraStole++;
					break;
				case 65:
					guthixStole++;
					break;
				case 66:
					zammyStole++;
					break;
				case 67:
					redBodyT++;
					break;
				case 68:
					redChapsT++;
					break;
				case 69:
					redBodyG++;
					break;
				case 70:
					redChapsG++;
					break;
				case 71:
					whiteCav++;
					break;
				case 72:
					redCav++;
					break;
				case 73:
					navyCav++;
					break;
				case 74:
					pithHelm++;
					break;
				case 75:
					explorerBackpack++;
					break;
				case 76:
					plateBandos++;
					break;
				case 77:
					platelegsBandos++;
					break;
				case 78:
					plateskirtBandos++;
					break;
				case 79:
					fullHelmBandos++;
					break;
				case 80:
					kiteBandos++;
					break;
				case 81:
					plateArmadyl++;
					break;
				case 82:
					platelegsArmadyl++;
					break;
				case 83:
					plateskirtArmadyl++;
					break;
				case 84:
					fullHelmArmadyl++;
					break;
				case 85:
					kiteArmadyl++;
					break;
				case 86:
					plateAncient++;
					break;
				case 87:
					platelegsAncient++;
					break;
				case 88:
					plateskirtAncient++;
					break;
				case 89:
					fullHelmAncient++;
					break;
				case 90:
					kiteAncient++;
					break;
				case 91:
					ancientBracers++;
					break;
				case 92:
					ancientDBody++;
					break;
				case 93:
					ancientChaps++;
					break;
				case 94:
					ancientCoif++;
					break;
				case 95:
					bandosBracers++;
					break;
				case 96:
					bandosDBody++;
					break;
				case 97:
					bandosChaps++;
					break;
				case 98:
					bandosCoifs++;
					break;
				case 99:
					armadylBracers++;
					break;
				case 100:
					armadylDBody++;
					break;
				case 101:
					armadylChaps++;
					break;
				case 102:
					armadylCoif++;
					break;
				case 103:
					greenMask++;
					break;
				case 104:
					blueMask++;
					break;
				case 105:
					redMask++;
					break;
				case 106:
					blackMask++;
					break;
				case 107:
					zombieHead++;
					break;
				case 108:
					nunchaku++;
					break;
				case 109:
					cyclopsHead++;
					break;
				case 110:
					ancientBoots++;
					break;
				case 111:
					bandosBoots++;
					break;
				case 112:
					guthixBoots++;
					break;
				case 113:
					armadylBoots++;
					break;
				case 114:
					saraBoots++;
					break;
				case 115:
					zammyBoots++;
					break;
				case 116:
					dragonBootsOrn++;
					break;
				case 117:
					dualSai++;
					break;
				case 118:
					thievingBag++;
					break;
				case 119:
					runeDefenderKit++;
					break;
				case 120:
					tzhaarKit++;
					break;
				case 121:
					berserkerKit++;
					break;
				case 122:
					runeCane++;
					break;
				}
				if (rareTable == 123)
				{
					int shieldRoll = rand() % 6 + 1;
					switch (shieldRoll)
					{
					case 1: guthixShield++;
						break;
					case 2: saraShield++;
						break;
					case 3: zammyShield++;
						break;
					case 4: ancientShield++;
						break;
					case 5: armadylShield++;
						break;
					case 6: bandosShield++;
						break;
					}
				}
				else if (rareTable == 124)
				{
					int heraldicRoll = rand() % 5 + 1;
					switch (heraldicRoll)
					{
					case 1: plateH1++;
						break;
					case 2: plateH2++;
						break;
					case 3: plateH3++;
						break;
					case 4: plateH4++;
						break;
					case 5: plateH5++;
						break;
					}
				}
				else if (rareTable == 125) // hit mega rare table
				{
					int megaRareTable = rand() % 10 + 1;
					if (megaRareTable == 1)
						superEnergy += 15;
					else if (megaRareTable == 2)
						superRestore += 15;
					else if (megaRareTable == 3)
						antifire += 15;
					else if (megaRareTable == 4)
						superSet += 15;
					else if (megaRareTable == 5)
					{
						int thirdAgeRoll = rand() % 13 + 1;
						if (thirdAgeRoll == 1)
							thirdHelm++;
						else if (thirdAgeRoll == 2)
							thirdPlate++;
						else if (thirdAgeRoll == 3)
							thirdLegs++;
						else if (thirdAgeRoll == 4)
							thirdSkirt++;
						else if (thirdAgeRoll == 5)
							thirdKite++;
						else if (thirdAgeRoll == 6)
							thirdCoif++;
						else if (thirdAgeRoll == 7)
							thirdRangeTop++;
						else if (thirdAgeRoll == 8)
							thirdRangeLegs++;
						else if (thirdAgeRoll == 9)
							thirdVambs++;
						else if (thirdAgeRoll == 10)
							thirdHat++;
						else if (thirdAgeRoll == 11)
							thirdRobeTop++;
						else if (thirdAgeRoll == 12)
							thirdRobeBottom++;
						else if (thirdAgeRoll == 13)
							thirdAmulet++;
					}
					else if (5 < megaRareTable < 11)
					{
						int gildRoll = rand() % 11 + 1;
						if (gildRoll == 1)
							gildFullHelm++;
						else if (gildRoll == 2)
							gildPlate++;
						else if (gildRoll == 3)
							gildLegs++;
						else if (gildRoll == 4)
							gildSkirt++;
						else if (gildRoll == 5)
							gildKite++;
						else if (gildRoll == 6)
							gildMed++;
						else if (gildRoll == 7)
							gildChain++;
						else if (gildRoll == 8)
							gildSq++;
						else if (gildRoll == 9)
							gild2h++;
						else if (gildRoll == 10)
							gildSpear++;
						else if (gildRoll == 11)
							gildHasta++;
					}
				}
			}
		}
		int master = rand() % 15 + 1;
		if (master == 1)
			extraMasterCount++;
		hardCounter++;

	}
	if (option == 1)
	{
		std::cout << "Total hard clues completed: " << hardCounter << '\n';
		std::cout << "Total masters: " << extraMasterCount << '\n';
		std::cout << "3rd Age Platebodies: " << thirdPlate << '\n';
		std::cout << "3rd Age Platelegs: " << thirdLegs << '\n';
		std::cout << "3rd Age Full Helms: " << thirdHelm << '\n';
		std::cout << "3rd Age KiteShields: " << thirdKite << '\n';
		std::cout << "3rd Age Plateskirts: " << thirdSkirt << '\n';
		std::cout << "3rd Age Robetop: " << thirdRobeTop << '\n';
		std::cout << "3rd Age Robebottom: " << thirdRobeBottom << '\n';
		std::cout << "3rd Age Mage Hat: " << thirdHat << '\n';
		std::cout << "3rd Age Amulet: " << thirdAmulet << '\n';
		std::cout << "3rd Age Coif: " << thirdCoif << '\n';
		std::cout << "3rd Age Range Top: " << thirdRangeTop << '\n';
		std::cout << "3rd Age Range Legs: " << thirdRangeLegs << '\n';
		std::cout << "3rd Age Vambs: " << thirdVambs << '\n';
		std::cout << "Super Sets: " << superSet << '\n';
		std::cout << "Super energies: " << superEnergy << '\n';
		std::cout << "Super restores: " << superRestore << '\n';
		std::cout << "Antifires: " << antifire << '\n';
		std::cout << "Gilded Platebodies: " << gildPlate << '\n';
		std::cout << "Gilded Platelegs: " << gildLegs << '\n';
		std::cout << "Gilded full helm: " << gildFullHelm << '\n';
		std::cout << "Gilded kiteshield: " << gildKite << '\n';
		std::cout << "Gilded plateskirt: " << gildSkirt << '\n';
		std::cout << "Gilded med helm: " << gildMed << '\n';
		std::cout << "Gilded chainbody: " << gildChain << '\n';
		std::cout << "Gilded square shield: " << gildSq << '\n';
		std::cout << "Gilded 2h: " << gild2h << '\n';
		std::cout << "Gilded spear: " << gildSpear << '\n';
		std::cout << "Gilded hasta: " << gildHasta << '\n';
		std::cout << "Bandos shield: " << bandosShield << '\n';
		std::cout << "Arma shield: " << armadylShield << '\n';
		std::cout << "Ancient shield: " << ancientShield << '\n';
		std::cout << "Zammy shield: " << zammyShield << '\n';
		std::cout << "Sara shield: " << saraShield << '\n';
		std::cout << "Guthix shield: " << guthixShield << '\n';
		std::cout << "Total Time spent: " << timer / 60 << '\n';
		std::cout << "Second hard cycle finished\n\n\n";
	}

	thirdAgeBox totalValue;
	totalValue.hardClues = hardCounter;
	totalValue.eliteClues = eliteCounter;
	totalValue.masterClues = masterCounter;
	totalValue.time = timer;
	return totalValue;
}

clueBox hardCluesBloodhound(int option)
{
	double masterCounter = 0, extraMasterCount = 0, eliteCounter = 0, hardCounter = 0, timer = 0;

	int superEnergy = 0, superRestore = 0, superSet = 0, gildedFullHelm = 0,

		robin = 0, plateT = 0, platelegsT = 0, kiteT = 0, fullHelmT = 0, plateG = 0, platelegsG = 0, kiteG = 0, fullHelmG = 0, plateZammy = 0, platelegsZammy = 0, kiteZammy = 0,
		fullHelmZammy = 0, plateSara = 0, platelegsSara = 0, kiteSara = 0, fullHelmSara = 0, plateGuthix = 0, platelegsGuthix = 0, kiteGuthix = 0, fullHelmGuthix = 0, tanCav = 0,
		darkCav = 0, blackCav = 0, pirateHat = 0, plateskirtG = 0, plateskirtT = 0, plateskirtZammy = 0, plateskirtSara = 0, plateskirtGuthix = 0, shieldH1 = 0, shieldH2 = 0, shieldH3 = 0,
		shieldH4 = 0, shieldH5 = 0, blueBodyG = 0, blueBodyT = 0, blueChapsG = 0, blueChapsT = 0, enchantedHat = 0, enchantedTop = 0, enchantedLegs = 0, helm1 = 0, helm2 = 0, helm3 = 0,
		helm4 = 0, helm5 = 0, gloryT = 0, zammyBracers = 0, zammyDBody = 0, zammyChaps = 0, zammyCoif = 0, guthixBracers = 0, guthixDBody = 0, guthixChaps = 0, guthixCoif = 0, saraBracers = 0,
		saraDBody = 0, saraChaps = 0, saraCoif = 0, saraCrozier = 0, guthixCrozier = 0, zammyCrozier = 0, saraStole = 0, guthixStole = 0, zammyStole = 0, redBodyT = 0, redChapsT = 0,
		redBodyG = 0, redChapsG = 0, whiteCav = 0, redCav = 0, navyCav = 0, pithHelm = 0, explorerBackpack = 0, plateBandos = 0, platelegsBandos = 0, plateskirtBandos = 0, fullHelmBandos = 0,
		kiteBandos = 0, plateArmadyl = 0, platelegsArmadyl = 0, plateskirtArmadyl = 0, fullHelmArmadyl = 0, kiteArmadyl = 0, plateAncient = 0, platelegsAncient = 0, plateskirtAncient = 0,
		fullHelmAncient = 0, kiteAncient = 0, ancientBracers = 0, ancientDBody = 0, ancientChaps = 0, ancientCoif = 0, bandosBracers = 0, bandosDBody = 0, bandosChaps = 0,
		bandosCoifs = 0, armadylBracers = 0, armadylDBody = 0, armadylChaps = 0, armadylCoif = 0, greenMask = 0, blueMask = 0, redMask = 0, blackMask = 0, zombieHead = 0, nunchaku = 0,
		cyclopsHead = 0, ancientBoots = 0, bandosBoots = 0, guthixBoots = 0, armadylBoots = 0, saraBoots = 0, zammyBoots = 0, dragonBootsOrn = 0, dualSai = 0, thievingBag = 0,
		runeDefenderKit = 0, tzhaarKit = 0, berserkerKit = 0, runeCane = 0, guthixShield = 0, saraShield = 0, zammyShield = 0, ancientShield = 0, armadylShield = 0, bandosShield = 0,
		plateH1 = 0, plateH2 = 0, plateH3 = 0, plateH4 = 0, plateH5 = 0;

	int nature = 0, crystal = 0, lavaMask = 0, battlestaff = 0, antifire = 0, restore = 0, brew = 0, range = 0, tuxJacket = 0, tuxCuffs = 0, tuxTrousers = 0,
		tuxShoes = 0, tuxBowTie = 0, lightTuxJacket = 0, lightTuxCuffs = 0, lightTuxTrousers = 0, lightTuxShoes = 0, lightTuxBowTie = 0;

	int occultO = 0, tortO = 0, anguishO = 0, tormentedO = 0, defO = 0, darkHood = 0, darkTop = 0, darkGloves = 0, darkBottom = 0, darkBoots = 0, samKasa = 0, samShirt = 0,
		samGloves = 0, samGreaves = 0, samBoots = 0, arcHood = 0, hosHood = 0, lovHood = 0, piscHood = 0, shayHood = 0, oldDemon = 0, lesserDemon = 0, greaterDemon = 0,
		blackDemon = 0, jungleDemon = 0, leftEye = 0, wig = 0, ale = 0, obsidian = 0, fancy = 0, halfMoon = 0, armadylO = 0, bandoO = 0, saraO = 0, zammyO = 0, dragonPlate = 0,
		ankouMask = 0, ankouTop = 0, ankouGloves = 0, ankouLegs = 0, ankouSocks = 0, mummyHead = 0, mummyBody = 0, mummyHands = 0, mummyLegs = 0, mummyFeet = 0, dragonKite = 0,
		thirdHelm = 0, thirdPlate = 0, thirdLegs = 0, thirdSkirt = 0, thirdKite = 0, thirdCoif = 0, thirdRangeTop = 0, thirdRangeLegs = 0, thirdVambs = 0,
		thirdHat = 0, thirdRobeTop = 0, thirdRobeBottom = 0, thirdAmulet = 0, thirdSword = 0, thirdWand = 0, thirdCloak = 0, thirdBow = 0, thirdDruidicStaff = 0, thirdDruidicCloak = 0,
		thirdDruidicTop = 0, thirdDruidicLegs = 0, thirdPick = 0, thirdAxe = 0, pet = 0, gildScim = 0, bucketG = 0, gildBoots = 0, ringCoins = 0, cabbage = 0, antiVenom = 0, torstol = 0,
		gildCoif = 0, gildVamb = 0, gildDTop = 0, gildChaps = 0, gildPick = 0, gildAxe = 0, gildSpade = 0, gildPlate = 0, gildLegs = 0, gildSkirt = 0, gildFullHelm = 0, gildKite = 0,
		gildMed = 0, gildChain = 0, gildSq = 0, gild2h = 0, gildSpear = 0, gildHasta = 0, mimicCount = 0, thirdAgeCount = 0;

	while (pet == 0)
	{
		timer += 6;
			int hardRolls = rand() % 3 + 4;
			for (int i = 0; i < hardRolls; i++)
			{
				int initialTable = rand() % 13 + 1;
				if (initialTable == 1) // hit rare table
				{
					int rareTable = rand() % 125 + 1;
					switch (rareTable)
					{
					case 1:
						robin++;
						break;
					case 2:
						plateT++;
						break;
					case 3:
						platelegsT++;
						break;
					case 4:
						kiteT++;
						break;
					case 5:
						fullHelmT++;
						break;
					case 6:
						plateG++;
						break;
					case 7:
						platelegsG++;
						break;
					case 8:
						kiteG++;
						break;
					case 9:
						fullHelmG++;
						break;
					case 10:
						plateZammy++;
						break;
					case 11:
						platelegsZammy++;
						break;
					case 12:
						kiteZammy++;
						break;
					case 13:
						fullHelmZammy++;
						break;
					case 14:
						plateSara++;
						break;
					case 15:
						platelegsSara++;
						break;
					case 16:
						kiteSara++;
						break;
					case 17:
						fullHelmSara++;
						break;
					case 18:
						plateGuthix++;
						break;
					case 19:
						platelegsGuthix++;
						break;
					case 20:
						kiteGuthix++;
						break;
					case 21:
						fullHelmGuthix++;
						break;
					case 22:
						tanCav++;
						break;
					case 23:
						darkCav++;
						break;
					case 24:
						blackCav++;
						break;
					case 25:
						pirateHat++;
						break;
					case 26:
						plateskirtG++;
						break;
					case 27:
						plateskirtT++;
						break;
					case 28:
						plateskirtZammy++;
						break;
					case 29:
						plateskirtSara++;
						break;
					case 30:
						plateskirtGuthix++;
						break;
					case 31:
						shieldH1++;
						break;
					case 32:
						shieldH2++;
						break;
					case 33:
						shieldH3++;
						break;
					case 34:
						shieldH4++;
						break;
					case 35:
						shieldH5++;
						break;
					case 36:
						blueBodyG++;
						break;
					case 37:
						blueBodyT++;
						break;
					case 38:
						blueChapsG++;
						break;
					case 39:
						blueChapsT++;
						break;
					case 40:
						enchantedHat++;
						break;
					case 41:
						enchantedTop++;
						break;
					case 42:
						enchantedLegs++;
						break;
					case 43:
						helm1++;
						break;
					case 44:
						helm2++;
						break;
					case 45:
						helm3++;
						break;
					case 46:
						helm4++;
						break;
					case 47:
						helm5++;
						break;
					case 48:
						gloryT++;
						break;
					case 49:
						zammyBracers++;
						break;
					case 50:
						zammyDBody++;
						break;
					case 51:
						zammyChaps++;
						break;
					case 52:
						zammyCoif++;
						break;
					case 53:
						guthixBracers++;
						break;
					case 54:
						guthixDBody++;
						break;
					case 55:
						guthixChaps++;
						break;
					case 56:
						guthixCoif++;
						break;
					case 57:
						saraBracers++;
						break;
					case 58:
						saraDBody++;
						break;
					case 59:
						saraChaps++;
						break;
					case 60:
						saraCoif++;
						break;
					case 61:
						saraCrozier++;
						break;
					case 62:
						guthixCrozier++;
						break;
					case 63:
						zammyCrozier++;
						break;
					case 64:
						saraStole++;
						break;
					case 65:
						guthixStole++;
						break;
					case 66:
						zammyStole++;
						break;
					case 67:
						redBodyT++;
						break;
					case 68:
						redChapsT++;
						break;
					case 69:
						redBodyG++;
						break;
					case 70:
						redChapsG++;
						break;
					case 71:
						whiteCav++;
						break;
					case 72:
						redCav++;
						break;
					case 73:
						navyCav++;
						break;
					case 74:
						pithHelm++;
						break;
					case 75:
						explorerBackpack++;
						break;
					case 76:
						plateBandos++;
						break;
					case 77:
						platelegsBandos++;
						break;
					case 78:
						plateskirtBandos++;
						break;
					case 79:
						fullHelmBandos++;
						break;
					case 80:
						kiteBandos++;
						break;
					case 81:
						plateArmadyl++;
						break;
					case 82:
						platelegsArmadyl++;
						break;
					case 83:
						plateskirtArmadyl++;
						break;
					case 84:
						fullHelmArmadyl++;
						break;
					case 85:
						kiteArmadyl++;
						break;
					case 86:
						plateAncient++;
						break;
					case 87:
						platelegsAncient++;
						break;
					case 88:
						plateskirtAncient++;
						break;
					case 89:
						fullHelmAncient++;
						break;
					case 90:
						kiteAncient++;
						break;
					case 91:
						ancientBracers++;
						break;
					case 92:
						ancientDBody++;
						break;
					case 93:
						ancientChaps++;
						break;
					case 94:
						ancientCoif++;
						break;
					case 95:
						bandosBracers++;
						break;
					case 96:
						bandosDBody++;
						break;
					case 97:
						bandosChaps++;
						break;
					case 98:
						bandosCoifs++;
						break;
					case 99:
						armadylBracers++;
						break;
					case 100:
						armadylDBody++;
						break;
					case 101:
						armadylChaps++;
						break;
					case 102:
						armadylCoif++;
						break;
					case 103:
						greenMask++;
						break;
					case 104:
						blueMask++;
						break;
					case 105:
						redMask++;
						break;
					case 106:
						blackMask++;
						break;
					case 107:
						zombieHead++;
						break;
					case 108:
						nunchaku++;
						break;
					case 109:
						cyclopsHead++;
						break;
					case 110:
						ancientBoots++;
						break;
					case 111:
						bandosBoots++;
						break;
					case 112:
						guthixBoots++;
						break;
					case 113:
						armadylBoots++;
						break;
					case 114:
						saraBoots++;
						break;
					case 115:
						zammyBoots++;
						break;
					case 116:
						dragonBootsOrn++;
						break;
					case 117:
						dualSai++;
						break;
					case 118:
						thievingBag++;
						break;
					case 119:
						runeDefenderKit++;
						break;
					case 120:
						tzhaarKit++;
						break;
					case 121:
						berserkerKit++;
						break;
					case 122:
						runeCane++;
						break;
					}
					if (rareTable == 123)
					{
						int shieldRoll = rand() % 6 + 1;
						switch (shieldRoll)
						{
						case 1: guthixShield++;
							break;
						case 2: saraShield++;
							break;
						case 3: zammyShield++;
							break;
						case 4: ancientShield++;
							break;
						case 5: armadylShield++;
							break;
						case 6: bandosShield++;
							break;
						}
					}
					else if (rareTable == 124)
					{
						int heraldicRoll = rand() % 5 + 1;
						switch (heraldicRoll)
						{
						case 1: plateH1++;
							break;
						case 2: plateH2++;
							break;
						case 3: plateH3++;
							break;
						case 4: plateH4++;
							break;
						case 5: plateH5++;
							break;
						}
					}
					else if (rareTable == 125) // hit mega rare table
					{
						int megaRareTable = rand() % 10 + 1;
						if (megaRareTable == 1)
							superEnergy += 15;
						else if (megaRareTable == 2)
							superRestore += 15;
						else if (megaRareTable == 3)
							antifire += 15;
						else if (megaRareTable == 4)
							superSet += 15;
						else if (megaRareTable == 5)
						{
							int thirdAgeRoll = rand() % 13 + 1;
							if (thirdAgeRoll == 1)
								thirdHelm++;
							else if (thirdAgeRoll == 2)
								thirdPlate++;
							else if (thirdAgeRoll == 3)
								thirdLegs++;
							else if (thirdAgeRoll == 4)
								thirdSkirt++;
							else if (thirdAgeRoll == 5)
								thirdKite++;
							else if (thirdAgeRoll == 6)
								thirdCoif++;
							else if (thirdAgeRoll == 7)
								thirdRangeTop++;
							else if (thirdAgeRoll == 8)
								thirdRangeLegs++;
							else if (thirdAgeRoll == 9)
								thirdVambs++;
							else if (thirdAgeRoll == 10)
								thirdHat++;
							else if (thirdAgeRoll == 11)
								thirdRobeTop++;
							else if (thirdAgeRoll == 12)
								thirdRobeBottom++;
							else if (thirdAgeRoll == 13)
								thirdAmulet++;
						}
						else if (5 < megaRareTable < 11)
						{
							int gildRoll = rand() % 11 + 1;
							if (gildRoll == 1)
								gildFullHelm++;
							else if (gildRoll == 2)
								gildPlate++;
							else if (gildRoll == 3)
								gildLegs++;
							else if (gildRoll == 4)
								gildSkirt++;
							else if (gildRoll == 5)
								gildKite++;
							else if (gildRoll == 6)
								gildMed++;
							else if (gildRoll == 7)
								gildChain++;
							else if (gildRoll == 8)
								gildSq++;
							else if (gildRoll == 9)
								gild2h++;
							else if (gildRoll == 10)
								gildSpear++;
							else if (gildRoll == 11)
								gildHasta++;
						}
					}
				}
			}
		int master = rand() % 15 + 1;
		if (master == 1)
			extraMasterCount++;
		hardCounter++;

		if (extraMasterCount > 0)
		{
			extraMasterCount--;
			timer += 15;
			for (int i = 0; i < 6; i++)
			{
				int roll = rand() % 23 + 1;
				if (roll == 23)
				{
					int rareRoll = rand() % 37 + 1;
					switch (rareRoll)
					{
					case 1: leftEye++;
						break;
					case 2: wig++;
						break;
					case 3: ale++;
						break;
					case 4: halfMoon++;
						break;
					case 5: fancy++;
						break;
					case 6: darkHood++;
						break;
					case 7: darkTop++;
						break;
					case 8: darkBottom++;
						break;
					case 9: darkBoots++;
						break;
					case 10: darkGloves++;
						break;
					case 11: obsidian++;
						break;
					case 12: occultO++;
						break;
					case 13: tortO++;
						break;
					case 14: defO++;
						break;
					case 15: samKasa++;
						break;
					case 16: samShirt++;
						break;
					case 17: samGreaves++;
						break;
					case 18: samBoots++;
						break;
					case 19: samGloves++;
						break;
					case 20: arcHood++;
						break;
					case 21: hosHood++;
						break;
					case 22: lovHood++;
						break;
					case 23: piscHood++;
						break;
					case 24: shayHood++;
						break;
					case 25: lesserDemon++;
						break;
					case 26: greaterDemon++;
						break;
					case 27: blackDemon++;
						break;
					case 28: jungleDemon++;
						break;
					case 29: oldDemon++;
						break;
					case 30: anguishO++;
						break;
					case 31: tormentedO++;
						break;
					case 32:
					{
						int megaRoll = rand() % 16 + 1;
						switch (megaRoll)
						{
						case 1: gildScim++;
							break;
						case 2: bucketG++;
							break;
						case 3: gildBoots++;
							break;
						case 4: ringCoins++;
							break;
						case 5: cabbage++;
							break;
						case 6: antiVenom++;
							break;
						case 7: torstol++;
							break;
						case 8: gildCoif++;
							break;
						case 9: gildVamb++;
							break;
						case 10: gildDTop++;
							break;
						case 11: gildChaps++;
							break;
						case 12: gildPick++;
							break;
						case 13: gildAxe++;
							break;
						case 14: gildSpade++;
							break;
						case 15:
						{
							int gildRoll = rand() % 11 + 1;
							switch (gildRoll)
							{
							case 1: gildPlate++;
								break;
							case 2: gildLegs++;
								break;
							case 3: gildSkirt++;
								break;
							case 4: gildFullHelm++;
								break;
							case 5: gildKite++;
								break;
							case 6: gildMed++;
								break;
							case 7: gildChain++;
								break;
							case 8: gildSq++;
								break;
							case 9: gild2h++;
								break;
							case 10: gildSpear++;
								break;
							case 11: gildHasta++;
								break;
							}
						}
						break;
						}
						if (megaRoll == 16)
						{
							int thirdTable = rand() % 23 + 1;
							if (thirdTable == 1)
								thirdCoif++;
							else if (thirdTable == 2)
								thirdRangeTop++;
							else if (thirdTable == 3)
								thirdRangeLegs++;
							else if (thirdTable == 4)
								thirdVambs++;
							else if (thirdTable == 5)
								thirdRobeTop++;
							else if (thirdTable == 6)
								thirdRobeBottom++;
							else if (thirdTable == 7)
								thirdHat++;
							else if (thirdTable == 8)
								thirdAmulet++;
							else if (thirdTable == 9)
								thirdLegs++;
							else if (thirdTable == 10)
								thirdPlate++;
							else if (thirdTable == 11)
								thirdHelm++;
							else if (thirdTable == 12)
								thirdSkirt++;
							else if (thirdTable == 13)
								thirdKite++;
							else if (thirdTable == 14)
								thirdSword++;
							else if (thirdTable == 15)
								thirdCloak++;
							else if (thirdTable == 16)
								thirdWand++;
							else if (thirdTable == 17)
								thirdBow++;
							else if (thirdTable == 18)
								thirdDruidicStaff++;
							else if (thirdTable == 19)
								thirdDruidicCloak++;
							else if (thirdTable == 20)
								thirdDruidicLegs++;
							else if (thirdTable == 21)
								thirdDruidicTop++;
							else if (thirdTable == 22)
								thirdPick++;
							else if (thirdTable == 23)
								thirdAxe++;
						}
					}
					case 33:
						break;
					case 34:
					{
						int godRoll = rand() % 4 + 1;
						if (godRoll == 1)
							armadylO++;
						else if (godRoll == 2)
							bandoO++;
						else if (godRoll == 3)
							zammyO++;
						else if (godRoll == 4)
							saraO++;
					}
					break;
					case 35:
					{
						int ankouRoll = rand() % 5 + 1;
						if (ankouRoll == 1)
							ankouMask++;
						else if (ankouRoll == 2)
							ankouTop++;
						else if (ankouRoll == 3)
							ankouLegs++;
						else if (ankouRoll == 4)
							ankouGloves++;
						else if (ankouRoll == 5)
							ankouSocks++;
					}
					break;
					case 36:
					{
						int mummyRoll = rand() % 5 + 1;
						if (mummyRoll == 1)
							mummyHead++;
						else if (mummyRoll == 2)
							mummyBody++;
						else if (mummyRoll == 3)
							mummyLegs++;
						else if (mummyRoll == 4)
							mummyFeet++;
						else if (mummyRoll == 5)
							mummyHands++;
					}
					break;
					case 37:
					{
						int coinRoll = rand() % 10 + 1;
						if (coinRoll == 10)
						{
							int dragonRoll = rand() % 3 + 1;
							if (dragonRoll == 1)
								dragonKite++;
							else
								dragonPlate++;
						}
					}
					break;
					}
				}

				int mimicRoll = rand() % 15 + 1;
				if (mimicRoll == 15)
				{
					int rareMimicRoll = rand() % 228 + 1;
					if (rareMimicRoll == 228)
					{
						int mimicThirdRoll = rand() % 23 + 1;
						if (mimicThirdRoll == 1)
							thirdCoif++;
						else if (mimicThirdRoll == 2)
							thirdRangeTop++;
						else if (mimicThirdRoll == 3)
							thirdRangeLegs++;
						else if (mimicThirdRoll == 4)
							thirdVambs++;
						else if (mimicThirdRoll == 5)
							thirdRobeTop++;
						else if (mimicThirdRoll == 6)
							thirdRobeBottom++;
						else if (mimicThirdRoll == 7)
							thirdHat++;
						else if (mimicThirdRoll == 8)
							thirdAmulet++;
						else if (mimicThirdRoll == 9)
							thirdLegs++;
						else if (mimicThirdRoll == 10)
							thirdPlate++;
						else if (mimicThirdRoll == 11)
							thirdHelm++;
						else if (mimicThirdRoll == 12)
							thirdSkirt++;
						else if (mimicThirdRoll == 13)
							thirdKite++;
						else if (mimicThirdRoll == 14)
							thirdSword++;
						else if (mimicThirdRoll == 15)
							thirdCloak++;
						else if (mimicThirdRoll == 16)
							thirdWand++;
						else if (mimicThirdRoll == 17)
							thirdBow++;
						else if (mimicThirdRoll == 18)
							thirdDruidicStaff++;
						else if (mimicThirdRoll == 19)
							thirdDruidicCloak++;
						else if (mimicThirdRoll == 20)
							thirdDruidicLegs++;
						else if (mimicThirdRoll == 21)
							thirdDruidicTop++;
						else if (mimicThirdRoll == 22)
							thirdPick++;
						else if (mimicThirdRoll == 23)
							thirdAxe++;
					}
				}
			}
			int petRoll = rand() % 1000 + 1;
			if (petRoll == 1)
				pet++;
			masterCounter++;
		}

	}
	if (option == 1)
	{
		std::cout << "Total hard clues completed: " << hardCounter << '\n';
		std::cout << "Super Sets: " << superSet << '\n';
		std::cout << "Super energies: " << superEnergy << '\n';
		std::cout << "Super restores: " << superRestore << '\n';
		std::cout << "Antifires: " << antifire << '\n';
		std::cout << "Gilded Platebodies: " << gildPlate << '\n';
		std::cout << "Gilded Platelegs: " << gildLegs << '\n';
		std::cout << "Gilded full helm: " << gildFullHelm << '\n';
		std::cout << "Gilded kiteshield: " << gildKite << '\n';
		std::cout << "Gilded plateskirt: " << gildSkirt << '\n';
		std::cout << "Gilded med helm: " << gildMed << '\n';
		std::cout << "Gilded chainbody: " << gildChain << '\n';
		std::cout << "Gilded square shield: " << gildSq << '\n';
		std::cout << "Gilded 2h: " << gild2h << '\n';
		std::cout << "Gilded spear: " << gildSpear << '\n';
		std::cout << "Gilded hasta: " << gildHasta << '\n';
		std::cout << "Bandos shield: " << bandosShield << '\n';
		std::cout << "Arma shield: " << armadylShield << '\n';
		std::cout << "Ancient shield: " << ancientShield << '\n';
		std::cout << "Zammy shield: " << zammyShield << '\n';
		std::cout << "Sara shield: " << saraShield << '\n';
		std::cout << "Guthix shield: " << guthixShield << '\n';
		std::cout << "Total 3rd age full helms: " << thirdHelm << '\n';
		std::cout << "Total 3rd age platebodies: " << thirdPlate << '\n';
		std::cout << "Total 3rd age platelegs: " << thirdLegs << '\n';
		std::cout << "Total 3rd age plateskirts: " << thirdSkirt << '\n';
		std::cout << "Total 3rd age kiteshields: " << thirdKite << '\n';
		std::cout << "Total 3rd age coifs: " << thirdCoif << '\n';
		std::cout << "Total 3rd age range tops: " << thirdRangeTop << '\n';
		std::cout << "Total 3rd age range legs: " << thirdRangeLegs << '\n';
		std::cout << "Total 3rd age vambs: " << thirdVambs << '\n';
		std::cout << "Total 3rd age mage hats: " << thirdHat << '\n';
		std::cout << "Total 3rd age robe tops: " << thirdRobeTop << '\n';
		std::cout << "Total 3rd age robe bottoms: " << thirdRobeBottom << '\n';
		std::cout << "Total 3rd age amulets: " << thirdAmulet << '\n';
		std::cout << "Total 3rd age wands: " << thirdWand << '\n';
		std::cout << "Total 3rd age bows: " << thirdBow << '\n';
		std::cout << "Total 3rd age cloaks: " << thirdCloak << '\n';
		std::cout << "Total 3rd age swords: " << thirdSword << '\n';
		std::cout << "Total 3rd age picks: " << thirdPick << '\n';
		std::cout << "Total 3rd age axe: " << thirdAxe << '\n';
		std::cout << "Total druidic tops: " << thirdDruidicTop << '\n';
		std::cout << "Total druidic legs: " << thirdDruidicLegs << '\n';
		std::cout << "Total druidic staff: " << thirdDruidicStaff << '\n';
		std::cout << "Total druidic cloaks: " << thirdDruidicCloak << '\n';
		std::cout << "Total master clues completed: " << masterCounter << '\n';
		std::cout << "Total Time spent: " << timer / 60 << '\n';
		std::cout << "First master cycle finished\n\n\n";
	}

	clueBox returns;
	returns.return1 = hardCounter;
	returns.return2 = masterCounter;
	returns.return3 = timer / 60;
	return returns;
}
