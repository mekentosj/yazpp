//
//  yaz-my-client.hpp
//  YAZPP
//
//  Created by Matias Piipari on 21/08/2014.
//  Copyright (c) 2014 Mekentosj BV. All rights reserved.
//

#ifndef YAZ_MYCLIENT_H
#define YAZ_MYCLIENT_H

#include <stdlib.h>
#include <yaz/log.h>
#include <yaz/options.h>
#include <yaz/diagbib1.h>
#include <yaz/marcdisp.h>
#include <yazpp/ir-assoc.h>
#include <yazpp/pdu-assoc.h>
#include <yazpp/socket-manager.h>
#include <yaz/oid_db.h>

using namespace yazpp_1;

class YAZ_EXPORT MyClient : public IR_Assoc {
private:
    int m_interactive_flag;
    char m_thisCommand[1024];
    char m_lastCommand[1024];
    int m_setOffset;
    SocketManager *m_socketManager;
public:
    MyClient(IPDU_Observable *the_PDU_Observable,
             SocketManager *the_SocketManager);
    IPDU_Observer *sessionNotify(IPDU_Observable *the_PDU_Observable, int fd);
    int args(SocketManager *socketManager, int argc, char **argv);
    int interactive(SocketManager *socketManager);
    int wait();
    void recv_initResponse(Z_InitResponse *initResponse);
    void recv_searchResponse(Z_SearchResponse *searchResponse);
    void recv_presentResponse(Z_PresentResponse *presentResponse);
    void recv_records (Z_Records *records);
    void recv_diagrecs(Z_DiagRec **pp, int num);
    void recv_namePlusRecord (Z_NamePlusRecord *zpr, int offset);
    void recv_record(Z_DatabaseRecord *record, int offset,
                     const char *databaseName);
    void recv_textRecord(const char *buf, size_t len);
    void recv_genericRecord(Z_GenericRecord *r);
    void connectNotify();
    void failNotify();
    void timeoutNotify();
    char *get_cookie (Z_OtherInformation **oi);
    int processCommand(const char *cmd);
    const char *getCommand();
    int cmd_open(char *host);
    int cmd_connect(char *host);
    int cmd_quit(char *args);
    int cmd_close(char *args);
    int cmd_find(char *args);
    int cmd_show(char *args);
    int cmd_cookie(char *args);
    int cmd_init(char *args);
    int cmd_format(char *args);
    int cmd_proxy(char *args);
};

#endif
