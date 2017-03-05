
const int CREATE_BYTE_SEND_WAIT = 15;

int main() {
	
	createInit();
	msleep(500);
	
	
	console_clear();
	set_a_button_text("");
	set_b_button_text("Play");
	set_c_button_text("");
	printf("Create connected successfully.\n\n");
	printf("Press \"Play\" to play song.\n\n");
	while (!b_button()) { msleep(10); }
	set_a_button_text("");
	set_b_button_text("");
	set_c_button_text("");
	printf("Playing...");
	
	playSong();
	
	
	//int theNumbers[19] = { 152, 17, 137, 1, 44, 128, 0, 156, 1, 144, 137, 1, 44, 0, 1, 157, 0, 90, 153 };
	
	//runScriptFromArray(theNumbers);
	
	return 0;
	
}

void runScriptFromArray(int array[]) {
	
	create_clear_serial_buffer();
	msleep(300);
	
	int size = 19;
	int i;
	
	for (i = 0; i < size; i++) {
		create_write_byte(array[i]);
		waitByteSendInterval();
	}
	
}

void playSong() {
	
	create_clear_serial_buffer();
	msleep(300);
	
	create_write_byte(128); //initializes mode to full
	waitByteSendInterval();
	create_write_byte(132);
	waitByteSendInterval();
	
	create_write_byte(152); //script size
	waitByteSendInterval();
	create_write_byte(49);
	waitByteSendInterval();
	
	
	
	create_write_byte(140); //define song 1
	waitByteSendInterval();
	create_write_byte(1);
	waitByteSendInterval();
	create_write_byte(4);
	waitByteSendInterval();
	
	create_write_byte(73);
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(71); 
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(73);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	create_write_byte(66);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	
	
	create_write_byte(140); //define song 2
	waitByteSendInterval();
	create_write_byte(2);
	waitByteSendInterval();
	create_write_byte(5);
	waitByteSendInterval();
	
	create_write_byte(74);
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(73);
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(74);
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(73);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	create_write_byte(71);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	
	
	create_write_byte(140); //define song 3
	waitByteSendInterval();
	create_write_byte(3);
	waitByteSendInterval();
	create_write_byte(5);
	waitByteSendInterval();
	
	create_write_byte(73);
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(71); 
	waitByteSendInterval();
	create_write_byte(8);
	waitByteSendInterval();
	
	create_write_byte(73);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	create_write_byte(66);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	create_write_byte(71);
	waitByteSendInterval();
	create_write_byte(32);
	waitByteSendInterval();
	
	create_write_byte(141); //play the first song
	waitByteSendInterval();
	create_write_byte(3);
	waitByteSendInterval();
	
	create_write_byte(155); 
	waitByteSendInterval();
	create_write_byte(15);
	waitByteSendInterval();
	
	create_write_byte(141); //play the second song
	waitByteSendInterval();
	create_write_byte(3);
	waitByteSendInterval();
	
	create_write_byte(155); 
	waitByteSendInterval();
	create_write_byte(15);
	waitByteSendInterval();
	
	create_write_byte(141); //play the third song
	waitByteSendInterval();
	create_write_byte(3);
	waitByteSendInterval();
	
	create_write_byte(155); 
	waitByteSendInterval();
	create_write_byte(15);
	waitByteSendInterval();
	
	create_write_byte(153); //Run it
	waitByteSendInterval();
	
}

void waitByteSendInterval() {
	msleep(CREATE_BYTE_SEND_WAIT);
}

void createInit() {
	
	console_clear();
	printf("The create must be turned on...");
	
	int connectionFailed = create_connect();
	
	msleep(200);
	
	if (!connectionFailed) {
		create_full();
		msleep(500);
		console_clear();
		printf("Create connection succeeded.\n\n");
		} else {
		msleep(500);
		console_clear();
		printf("Create connection failed.\n\n");
	}
	
}
