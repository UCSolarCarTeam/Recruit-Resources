package main

import (
    "crypto/sha256"
    "fmt"
    "io"
    "net/http"
    "os"
)

func challenge(w http.ResponseWriter, r *http.Request) {
    if r.Method == "POST" {
        r.ParseForm()
        var name string
        var UCID string

        requestLog, err := os.OpenFile("RequestLog.txt", os.O_APPEND|os.O_WRONLY, 0600)
        if err != nil {
            panic(err)
        }
        defer requestLog.Close()

        if val, ok := r.Form["Name"]; ok {
            name = val[0]
        } else {
            requestLog.WriteString(fmt.Sprintln("Bad request: ", r.Form, "\n"))
            fmt.Fprintf(w, "\nBad Request\n")
            return
        }

        if val, ok := r.Form["UCID"]; ok {
            UCID = val[0]
        } else {
            requestLog.WriteString(fmt.Sprintln("Bad request: ", r.Form, "\n"))
            fmt.Fprintf(w, "\nBad Request\n")
            return
        }

        if len(name) > 100 {
            requestLog.WriteString(fmt.Sprintln("WARNING: Got a name length of ", len(name)))
            fmt.Fprintf(w, "\nYou have a very long name! Send less than 100 chars please :)\n")
            return
        }

        hasher := sha256.New()
        io.WriteString(hasher, name)
        hash := fmt.Sprintf("%x", hasher.Sum(nil))

        message := `Thanks for applying to the University of Calgary Solar Car Software Team! Please copy this entire message and email it to 'software@calgarysolarcar.ca'. We will get back to you as soon as possible. If you would like more information about the Solar Car Team, there are info sessions September 28th and 29th at 5:30PM in ENG 230.`
        message += "\n\nName: " + name + "\n"
        message += "Hash: " + hash + "\n"
        message += "UCID: " + UCID + "\n"

        success := fmt.Sprintln("Name: " + name)
        success += fmt.Sprintln("Hash: " + hash)
        success += fmt.Sprintln("UCID: " + UCID + "\n")
        requestLog.WriteString(success)

        successLog, _ := os.OpenFile("SuccessLog.txt", os.O_APPEND|os.O_WRONLY, 0600)
        defer successLog.Close()

        successLog.WriteString(success)

        fmt.Fprintf(w, message)
    }
}

func main() {
    http.HandleFunc("/", challenge)

    err := http.ListenAndServe(":8456", nil)
    if err != nil {
        fmt.Println(err)
    }

}
