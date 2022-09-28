#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <security/_pam_types.h>
#include <string>
#include <security/pam_appl.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "login.h"

using namespace std;

struct pam_response *reply;

int login_covc(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr){
    char *username;
    char *password;
    int ok = PAM_SUCCESS;
    int i;

    *resp = (struct pam_response*)calloc(num_msg, sizeof(struct pam_response));
    
    if(*resp == NULL){
        return PAM_BUF_ERR;
    }

    for(i = 0; i < num_msg; i++){
        switch (msg[i]->msg_style) {
            case PAM_PROMPT_ECHO_ON:{
                username = ((char**) appdata_ptr)[0];
                resp[i]->resp = strdup(username);
                break;
            } case PAM_PROMPT_ECHO_OFF:{
                password = ((char**) appdata_ptr)[1];
                resp[i]->resp = strdup(password);
                break;
            } case PAM_ERROR_MSG:{
                ok = PAM_CONV_ERR;
                break;
            }
        }

        if(ok != PAM_SUCCESS){
            break;
        }
    }

    if(ok != PAM_SUCCESS){
        for(i = 0; i < num_msg; i++){
            if((*resp[i]).resp == NULL){
                continue;
            }
            free((*resp)[i].resp);
            (*resp)[i].resp = NULL;
        }
        free(*resp);
    }

    return ok;

}


int auth(char *username, char *password){
    int ok = 0;
    int ret = 0;
    char *creds[2] = {username, password};

    
    pam_handle_t *handle = NULL;
    static struct pam_conv conv = {login_covc, creds};


    ret = pam_start("system-login", NULL, &conv, &handle);
    if(ret != PAM_SUCCESS){
        return PAM_ABORT;
    }

    ok = pam_authenticate(handle, 0);

    //ret = pam_acct_mgmt(handle, 0);
//
    //if(ret != PAM_SUCCESS){
    //    return PAM_ABORT;
    //}
//
    //ret = pam_setcred(handle, PAM_ESTABLISH_CRED);
//
    //if(ret != PAM_SUCCESS){
    //    return PAM_ABORT;
    //}
//
    //ret = pam_open_session(handle, 0);
//
    //if(ret != PAM_SUCCESS){
    //    return PAM_ABORT;
    //}   
//
    //ret = pam_end(handle, ret);
//
    //if(ret != PAM_SUCCESS){
    //    cout << "oopsi woopsise, something went wong" << endl;
    //}

    struct passwd* pwd = getpwnam(username);
    endpwent();

    if(pwd != NULL){
        cout << pwd->pw_shell << endl;
        sleep(2);
    }

    return ok;
}