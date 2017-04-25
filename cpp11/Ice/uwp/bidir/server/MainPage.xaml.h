﻿// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#pragma once

#include "MainPage.g.h"
#include <Ice/Ice.h>
#include <Callback.h>

namespace bidir
{
ref class MainPage;

class CallbackSenderI : public Demo::CallbackSender,
                        public std::enable_shared_from_this<CallbackSenderI>
{
public:

    CallbackSenderI(MainPage^ page);

    virtual void addClient(Ice::Identity, const Ice::Current&) override;
    void start();    

private:

    void invokeCallback();
    void removeClient(const std::shared_ptr<Demo::CallbackReceiverPrx>&, std::exception_ptr);

    MainPage^ _page;
    bool _destroy;
    std::vector<std::shared_ptr<Demo::CallbackReceiverPrx>> _clients;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::future<void> _result;
};

public ref class MainPage sealed
{
public:
    MainPage();

private:

    friend class CallbackSenderI;

    void print(const std::string&);

    std::shared_ptr<Ice::Communicator> _communicator;
    std::shared_ptr<Ice::ObjectAdapter> _adapter;
    std::shared_ptr<CallbackSenderI> _sender;
};

}
