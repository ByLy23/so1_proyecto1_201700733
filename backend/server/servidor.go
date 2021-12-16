package main

import(
	"fmt"
	"log"
	"net/http"
	"io/ioutil"
	"os/exec"
	"encoding/json"
)

func endpountFunc(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Todo ok");
}
func leerArchivo(w http.ResponseWriter, r *http.Request) {
	go fmt.Println("Request al endpoint de inicio.de memoria..");
	out,err:=ioutil.ReadFile("/proc/memo_201700733");
	if err!=nil {
		log.Fatal(err);
	}
	output := string(out[:]);
	var dataStruct struct {
		ram int
		used int
		avg int
	}
	json.Unmarshal([]byte(output),&dataStruct)
	w.Write(dataStruct)
}
func leerCPU(w http.ResponseWriter, r *http.Request) {
	go fmt.Println("Request al endpoint de inicio.de CPU..");
	out,err:=ioutil.ReadFile("/proc/cpu_201700733");
	if err!=nil {
		log.Fatal(err);
	}
	output := string(out[:]);
	fmt.Fprintf(w, output);
}
func matarProceso(w http.ResponseWriter, r *http.Request) {
	go fmt.Println("Request al endpoint de Kill proceso..");
	keys, ok:= r.URL.Query()["pid"]
	if !ok || len(keys[0])<1 {
		return
	}
	var salida string= keys[0]
	cmd:=exec.Command("sh","-c","echo Amoal1l1...' | sudo -S kill "+salida);
	out,err:=cmd.CombinedOutput()
	if err!=nil {
		log.Fatal(err);
	}
	output := string(out[:]);
	fmt.Fprintf(w, output);
}
//getent passwd var | cut -d: -f1
func main(){
	go fmt.Println("Servidor levantado...");

	http.HandleFunc("/",endpountFunc);
	http.HandleFunc("/iniMemo",leerArchivo);
	http.HandleFunc("/iniCpu",leerCPU);
	http.HandleFunc("/mataProceso",matarProceso);

	err:= http.ListenAndServe(":8000",nil);
	if err!=nil{
		log.Fatal(err);
	}
}
//TERMINAR PROCESOS
//MOSTRAR CPU
//MOSTRAR MEMORIA
//MOSTRAR PORCENTAJE MEMORIA
//MOSTRAR PORCENTAJE CPU