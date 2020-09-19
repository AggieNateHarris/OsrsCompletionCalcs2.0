/*#include <iostream>
#include <random>
#include <time.h>
#include <queue>
#include <math.h>
#include <string>
#include <fstream>

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

struct clueBox
{
	int return1;
	int return2;
	int return3;
};

int armadyl(int option, bool petOnly);
int abyssalSire(int option, bool petOnly);
int beginnerClue(int option);
clueBox easyClue(int option);
clueBox mediumClue(int option);
int alchemicalHydra(int option, bool petOnly);
int cerberus(int option, bool petOnly);
int zily(int option, bool petOnly);
int graardor(int option, bool petOnly);
int grotGuardians(int option, bool petOnly);
int kraken(int option, bool petOnly);
int kril(int option, bool petOnly);
int thermy(int option, bool petOnly);
thirdAgeBox efficientThirdAgeTwo(int option);

int main()
{
	srand(time(NULL));

	int retry = -1;

	while (retry != 0)
	{
		if (retry == 5)
			armadyl(1, 0);
		else if (retry == 6)
		{
		int avg = 0;
		std::priority_queue<int> finishedSet;
		const int TRIALS = 25000;
		for (int i = 0; i < TRIALS; i++) // sort as being populated
		{
			int holder = armadyl(0, 0);
			avg += holder;
			finishedSet.push(holder);
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
		else if (retry == 9)
			abyssalSire(1, 0);
		else if (retry == 10)
		{
			const int TRIALS = 25000;
			int avg = 0;
			std::priority_queue<int> finishedSet;
			for (int i = 0; i < TRIALS; i++) // sort as being populated
			{
				int finished = abyssalSire(0, 0);
				avg += finished;
				finishedSet.push(finished);
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
		else if (retry == 35)
			alchemicalHydra(1, 0);
		else if (retry == 36)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedHydra;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = alchemicalHydra(0, 0);
			avg += holder;
			int finished = holder;
			finishedHydra.push(finished);
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
		else if (retry == 39)
			cerberus(1, 0);
		else if (retry == 40)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedCerberus;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = cerberus(0, 0);
			avg += holder;
			int finished = holder;
			finishedCerberus.push(finished);
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
		else if (retry == 45)
			zily(1, 0);
		else if (retry == 46)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedSet;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = zily(0, 0);
			avg += holder;
			int finished = holder;
			finishedSet.push(finished);
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
		else if (retry == 49)
			graardor(1, 0);
		else if (retry == 50)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedSet;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = graardor(0, 0);
			avg += holder;
			int finished = holder;
			finishedSet.push(finished);
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
		else if (retry == 53)
			grotGuardians(1, 0);
		else if (retry == 54)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedSet;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = grotGuardians(0, 0);
			avg += holder;
			int finished = holder;
			finishedSet.push(finished);
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
		else if (retry == 59)
			kraken(1, 0);
		else if (retry == 60)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedSet;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = kraken(0, 0);
			avg += holder;
			int finished = holder;
			finishedSet.push(finished);
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
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedSet;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = kril(0, 0);
			avg += holder;
			int finished = holder;
			finishedSet.push(finished);
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
		else if (retry == 71)
			thermy(1, 0);
		else if (retry == 72)
		{
		const int TRIALS = 25000;
		int avg = 0, holder = 0;
		std::priority_queue<int> finishedSet;
		for (int i = 0; i < TRIALS; i++)
		{
			holder = thermy(0, 0);
			avg += holder;
			int finished = holder;
			finishedSet.push(finished);
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
		for (int i = 0; i < TRIALS / 2; i++)
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
		for (int i = 0; i < TRIALS / 2 - 1; i++)
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
	}

	return 0;
}

int armadyl(int option, bool petOnly)
{
	int armadylHelm = 0, armadylChest = 0, armadylSkirt = 0, armadylHilt = 0, armadylPet = 0, shard1 = 0, shard2 = 0, shard3 = 0, counter = 0;
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
		}
		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total armadyl helms: " << armadylHelm << '\n';
			std::cout << "Total armadyl chestplates: " << armadylChest << '\n';
			std::cout << "Total armadyl plateskirts: " << armadylSkirt << '\n';
			std::cout << "Total armadyl hilts: " << armadylHilt << '\n';
			std::cout << "Total armadyl pets: " << armadylPet << '\n';
		}
		return counter;
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
		}
		if (option == 1)
		{
			std::cout << "Total kills: " << counter << '\n';
			std::cout << "Total armadyl helms: " << armadylHelm << '\n';
			std::cout << "Total armadyl chestplates: " << armadylChest << '\n';
			std::cout << "Total armadyl plateskirts: " << armadylSkirt << '\n';
			std::cout << "Total armadyl hilts: " << armadylHilt << '\n';
			std::cout << "Total armadyl pets: " << armadylPet << '\n';
		}
		return counter;
	}
}

int abyssalSire(int option, bool petOnly)
{
	int jar = 0, head = 0, whip = 0, bludgeon = 0, dagger = 0, pet = 0, counter = 0;
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
		}
		if (option == 1)
		{
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total abby heads: " << head << '\n';
			std::cout << "Total whips: " << whip << '\n';
			std::cout << "Total bludgeons: " << bludgeon / 3 << "(" << bludgeon % 3 << ")" << '\n';
			std::cout << "Total daggers: " << dagger << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total kills: " << counter << '\n';
		}
		return counter;
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
		}
		if (option == 1)
		{
			std::cout << "Total jars: " << jar << '\n';
			std::cout << "Total abby heads: " << head << '\n';
			std::cout << "Total whips: " << whip << '\n';
			std::cout << "Total bludgeons: " << bludgeon / 3 << "(" << bludgeon % 3 << ")" << '\n';
			std::cout << "Total daggers: " << dagger << '\n';
			std::cout << "Total pets: " << pet << '\n';
			std::cout << "Total kills: " << counter << '\n';
		}
		return counter;
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
		blueEleSkirt == 0 || teamZero == 0 || teamI == 0 || teamX == 0 || skulls == 0 || monkTopG == 0 || monkBottomG == 0)
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
				if (coinRoll < 5)
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

int alchemicalHydra(int option, bool petOnly)
{
	int dragonAxe = 0, dragonKnife = 0, hydraClaw = 0, hydraTail = 0, hydraLeather = 0, brimstoneRing = 0, pet = 0, killcount = 0, jar = 0;
	if (petOnly == 0)
	{
		while (dragonAxe == 0 || dragonKnife == 0 || hydraClaw == 0 || hydraTail == 0 || hydraLeather == 0 || brimstoneRing < 4 || pet == 0 || jar == 0)
		{
			int roll = 0, roll2 = 0, roll3 = 0, roll4 = 0, roll5 = 0, roll6 = 0, petRoll = 0;
			petRoll = rand() % 100 + 1; //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}

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
		}
		return killcount;
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
		}

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
		}
		return killcount;
	}
}

int cerberus(int option, bool petOnly)
{
	int hellPuppy = 0, prim = 0, peg = 0, etern = 0, smould = 0, jar = 0, killcount = 0;
	if (petOnly == 0)
	{
		while (hellPuppy == 0 || jar == 0 || prim == 0 || peg == 0 || etern == 0 || smould == 0)
		{
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, much more accurate
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
		}
		if (option == 1)
		{
			std::cout << "You completed Cerberus in " << killcount << " kills.\n";
			std::cout << "Hellpuppies: " << hellPuppy << '\n';
			std::cout << "Primordial crystals: " << prim << '\n';
			std::cout << "Pegasian crystals: " << peg << '\n';
			std::cout << "Eternal crystals: " << etern << '\n';
			std::cout << "Smouldering crystals: " << smould << '\n';
		}
		return killcount;
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
		}
		if (option == 1)
		{
			std::cout << "You completed Cerberus in " << killcount << " kills.\n";
			std::cout << "Hellpuppies: " << hellPuppy << '\n';
			std::cout << "Primordial crystals: " << prim << '\n';
			std::cout << "Pegasian crystals: " << peg << '\n';
			std::cout << "Eternal crystals: " << etern << '\n';
			std::cout << "Smouldering crystals: " << smould << '\n';
		}
		return killcount;
	}
}

int zily(int option, bool petOnly)
{
	int killcount = 0, sword = 0, light = 0, cbow = 0, hilt = 0, pet = 0, shard1 = 0, shard2 = 0, shard3 = 0;
	if (petOnly == 0)
	{
		while (sword == 0 || light == 0 || cbow == 0 || hilt == 0 || pet == 0  || shard1 == 0 || shard2 == 0 || shard3 == 0)
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
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}
		if (option == 1)
		{
			std::cout << "To completed Zilyana in " << killcount << " kills.\n";
			std::cout << "Pet Zilyanas: " << pet << '\n';
			std::cout << "Saraswords: " << sword << '\n';
			std::cout << "Sara lights: " << light << '\n';
			std::cout << "Armadyl Crossbows: " << cbow << '\n';
			std::cout << "Sara Hilts: " << hilt << '\n';
		}
		return killcount;
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
		}
		if (option == 1)
		{
			std::cout << "To completed Zilyana in " << killcount << " kills.\n";
			std::cout << "Pet Zilyanas: " << pet << '\n';
			std::cout << "Saraswords: " << sword << '\n';
			std::cout << "Sara lights: " << light << '\n';
			std::cout << "Armadyl Crossbows: " << cbow << '\n';
			std::cout << "Sara Hilts: " << hilt << '\n';
		}
		return killcount;
	}
}

int graardor(int option, bool petOnly)
{
	int killcount = 0, tassy = 0, chest = 0, boots = 0, hilt = 0, pet = 0, shard1 = 0, shard2 = 0, shard3 = 0;
	if (petOnly == 0)
	{
		while (tassy == 0 || chest == 0 || boots == 0 || hilt == 0 || pet == 0  || shard1 == 0 || shard2 == 0 || shard3 == 0)
		{
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}
		if (option == 1)
		{
			std::cout << "You finished graardor in " << killcount << " kills.\n";
			std::cout << "Pet Graardors: " << pet << '\n';
			std::cout << "Bandos Hilts: " << hilt << '\n';
			std::cout << "Bandos Tassys: " << tassy << '\n';
			std::cout << "Bandos Chestplate: " << chest << '\n';
			std::cout << "Bandos Boots: " << boots << '\n';
		}
		return killcount;
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
		}
		if (option == 1)
		{
			std::cout << "You finished graardor in " << killcount << " kills.\n";
			std::cout << "Pet Graardors: " << pet << '\n';
			std::cout << "Bandos Hilts: " << hilt << '\n';
			std::cout << "Bandos Tassys: " << tassy << '\n';
			std::cout << "Bandos Chestplate: " << chest << '\n';
			std::cout << "Bandos Boots: " << boots << '\n';
		}
		return killcount;
	}
}

int grotGuardians(int option, bool petOnly)
{
	int killcount = 0, maul = 0, gloves = 0, ring = 0, hammer = 0, core = 0, pet = 0, jar = 0;
	if (petOnly == 0)
	{
		while (maul == 0 || gloves == 0 || ring == 0 || hammer == 0 || core == 0 || pet == 0 || jar == 0)
		{
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}
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
		}
		return killcount;
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
		}
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
		}
		return killcount;
	}
}

int kraken(int option, bool petOnly)
{
	int killcount = 0, tent = 0, trident = 0, jar = 0, pet = 0;
	if (petOnly == 0)
	{
		while (pet == 0 || jar == 0 || tent == 0 || trident == 0)
		{
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}
		if (option == 1)
		{
			std::cout << "You finished kraken in " << killcount << " kills.\n";
			std::cout << "Jars of swamp: " << jar << '\n';
			std::cout << "Pets: " << pet << '\n';
			std::cout << "Kraken Tentacles: " << tent << '\n';
			std::cout << "Tridents(full): " << trident << '\n';
		}
		return killcount;
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
		}
		if (option == 1)
		{
			std::cout << "You finished kraken in " << killcount << " kills.\n";
			std::cout << "Jars of swamp: " << jar << '\n';
			std::cout << "Pets: " << pet << '\n';
			std::cout << "Kraken Tentacles: " << tent << '\n';
			std::cout << "Tridents(full): " << trident << '\n';
		}
		return killcount;
	}
}

int kril(int option, bool petOnly)
{
	int killcount = 0, steam = 0, spear = 0, staffDead = 0, hilt = 0, pet = 0, shard1 = 0, shard2 = 0, shard3 = 0;
	if (petOnly == 0)
	{
		while (steam == 0 || spear == 0 || staffDead == 0 || hilt == 0 || shard1 == 0 || shard2 == 0 || shard3 == 0 || pet == 0)
		{
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}
		if (option == 1)
		{
			std::cout << "You finished kril in " << killcount << " kills.\n";
			std::cout << "Zammy pets: " << pet << '\n';
			std::cout << "Zammy spears: " << spear << '\n';
			std::cout << "Steam battlestaves: " << steam << '\n';
			std::cout << "Zammy hilts: " << hilt << '\n';
			std::cout << "Staff of dead: " << staffDead << '\n';
		}
		return killcount;
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
		}
		if (option == 1)
		{
			std::cout << "You finished kril in " << killcount << " kills.\n";
			std::cout << "Zammy pets: " << pet << '\n';
			std::cout << "Zammy spears: " << spear << '\n';
			std::cout << "Steam battlestaves: " << steam << '\n';
			std::cout << "Zammy hilts: " << hilt << '\n';
			std::cout << "Staff of dead: " << staffDead << '\n';
		}
		return killcount;
	}
}

int thermy(int option, bool petOnly)
{
	int killcount = 0, occult = 0, staff = 0, chain = 0, pet = 0;
	if (petOnly == 0)
	{
		while (occult == 0 || staff == 0 || chain == 0 || pet == 0)
		{
			int petRoll = rand() % 100 + 1;  //Having a rand() % 5000 was giving weird results, an average of 4.8k kills to finish which is obviously wrong. Split into smaller chunks, seems more accurate
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
		}
		if (option == 1)
		{
			std::cout << "You finished thermy in " << killcount << " kills.\n";
			std::cout << "Thermy Pets: " << pet << '\n';
			std::cout << "Dragon Chain: " << chain << '\n';
			std::cout << "Occult necklace: " << occult << '\n';
			std::cout << "Smoke Battlestaves: " << staff << '\n';
		}
		return killcount;
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
		}
		if (option == 1)
		{
			std::cout << "You finished thermy in " << killcount << " kills.\n";
			std::cout << "Thermy Pets: " << pet << '\n';
			std::cout << "Dragon Chain: " << chain << '\n';
			std::cout << "Occult necklace: " << occult << '\n';
			std::cout << "Smoke Battlestaves: " << staff << '\n';
		}
		return killcount;
	}
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
	while (robin == 0 || plateT == 0 || platelegsT == 0 || kiteT == 0 || fullHelmT == 0 || plateG == 0 || platelegsG == 0 || kiteG == 0 || fullHelmG == 0 || plateZammy == 0 || platelegsZammy == 0 || kiteZammy == 0 ||
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
		thirdRobeBottom == 0 || thirdRobeTop == 0 || thirdHat == 0 || thirdRangeLegs == 0 || thirdRangeTop == 0 || thirdCoif == 0 || thirdVambs == 0 /*trueCheck == false)
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

*/