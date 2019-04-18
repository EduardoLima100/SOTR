//Aula01

main(){
	//initialization code here
	while(1){
		currTemp = tempRead();
		lcdWrite(currTemp);
		//waste CPU cycles until 50ms
		currTemp = tempRead();
		//do other stuff
		//waste CPU cycles until 100ms
	}
}