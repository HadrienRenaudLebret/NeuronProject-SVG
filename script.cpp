#include "script.h"

using namespace std;

void scriptFile(ifstream &input)
{
	std::vector<string> cmdsVect;
	string cmdName;

	while(input >> cmdName)
	{
		cmdsVect.push_back(cmdName);
	}

	string cmds[cmdsVect.size()];
	for (int i = 0; i < (int)cmdsVect.size(); ++i)
		cmds[i]=cmdsVect[i];

	std::cout << cmdsVect.size() << "\n";

	input.close();

	commands(cmdsVect.size(),cmds);
}

void commands(int nbCmds, string cmds[])
{
	int length_alphabet = getLenghtAlphabet();
	std::cout << length_alphabet << "\n";
	NetworkArray* tablo_net = new NetworkArray(length_alphabet);

	for (int i = 0; i < nbCmds; ++i)
	{
		cout << i << " : " << cmds[i] <<endl;

		if (cmds[i] == "new")
		{
			if (tablo_net)
				delete tablo_net;
			NetworkArray* tablo_net = new NetworkArray(length_alphabet);
		}

		else if (cmds[i] == "save")
		{
			if (tablo_net)
				tablo_net->save();
			else
				cout << "Réseaux vides" <<endl;
		}

		else if (cmds[i] == "learn")
			tablo_net->learnAllNetworks();

	  #ifndef NO_GRAPHIC
		else if (cmds[i] == "filter")
			filtres();

		else if (cmds[i] == "database")
			database(false, true);
	  #endif

		else if (cmds[i] == "test")
		{
      #ifndef NO_GRAPHIC
			filtres(DOSSIERTEST, DOSSIERTESTTEXT, true);
      #endif //NO_GRAPHIC
			tablo_net->testAll();

		}

		cout << endl;
	}

	if (tablo_net)
		delete tablo_net;
}

int getLenghtAlphabet()
{
	ifstream	optionsFile(NAME_CONFIG_FILE);
	string		line;
	string		cmdName;
	string		bin;
	string		cmdValueStr;
	int		cmdValue = LENGTH_ALPHABET;

	while (getline(optionsFile, line))
	{
		if (!(line.length() == 0 || line[0] == '#'))
		{
			istringstream line_stream(line);
			line_stream >> cmdName;
			line_stream >> bin;
			line_stream >> cmdValueStr;

			if (cmdName == "length_alphabet")
				cmdValue = atoi(cmdValueStr.c_str());
		}
	}
	return cmdValue;
}
