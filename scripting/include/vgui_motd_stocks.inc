// TODO register cache buster as a shared plugin?
// have to figure out some way to ensure these extended features are discoverable

// if 0 cache buster will not pass dimensions to proxy page and assume default
#define CSGO_POPUP_FULL 0

/**
 * Displays an MOTD panel with CS:GO-specific options
 */
stock void CSGO_ShowMOTDPanel(int client, const char[] title, const char[] url,
		bool show = false, int width = CSGO_POPUP_FULL, int height = CSGO_POPUP_FULL) {
	if (!IsClientInGame(client) || IsFakeClient(client)) {
		return;
	}

	//Send VGUI message without with USERMSG_BLOCKHOOKS flag
	int players[1];
	players[0] = client;
	Handle msg = StartMessage("VGUIMenu", players, 1);
	Protobuf pb = UserMessageToProtobuf(msg);

	pb.SetString("name", "info");
	pb.SetBool("show", show);

	char buffer[64];

	Protobuf subkey;

	//Set custom fields for width and height
	if (show) {
		subkey = pb.AddMessage("subkeys");
		IntToString(width, buffer, sizeof(buffer));
		subkey.SetString("name", "x-vgui-width");
		subkey.SetString("str", buffer);

		subkey = pb.AddMessage("subkeys");
		IntToString(height, buffer, sizeof(buffer));
		subkey.SetString("name", "x-vgui-height");
		subkey.SetString("str", buffer);
	}

	//Set standard fields
	subkey = pb.AddMessage("subkeys");
	subkey.SetString("name", "title");
	subkey.SetString("str", title);

	subkey = pb.AddMessage("subkeys");
	IntToString(MOTDPANEL_TYPE_URL, buffer, sizeof(buffer));
	subkey.SetString("name", "type");
	subkey.SetString("str", buffer);

	subkey = pb.AddMessage("subkeys");
	subkey.SetString("name", "msg");
	subkey.SetString("str", url);

	EndMessage();
}

/**
 * Displays an MOTD panel to a client using the given KeyValues handle as the subkeys.
 */
stock void ShowMOTDPanelEx(int client, bool show, KeyValues subkeys) {
	// TODO send a message using KV handle as key/values
	// support both bitbuffers and protobufs
}
