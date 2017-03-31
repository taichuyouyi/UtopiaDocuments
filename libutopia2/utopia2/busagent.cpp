/*****************************************************************************
 *  
 *   This file is part of the Utopia Documents application.
 *       Copyright (c) 2008-2017 Lost Island Labs
 *           <info@utopiadocs.com>
 *   
 *   Utopia Documents is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU GENERAL PUBLIC LICENSE VERSION 3 as
 *   published by the Free Software Foundation.
 *   
 *   Utopia Documents is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 *   Public License for more details.
 *   
 *   In addition, as a special exception, the copyright holders give
 *   permission to link the code of portions of this program with the OpenSSL
 *   library under certain conditions as described in each individual source
 *   file, and distribute linked combinations including the two.
 *   
 *   You must obey the GNU General Public License in all respects for all of
 *   the code used other than OpenSSL. If you modify file(s) with this
 *   exception, you may extend this exception to your version of the file(s),
 *   but you are not obligated to do so. If you do not wish to do so, delete
 *   this exception statement from your version.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with Utopia Documents. If not, see <http://www.gnu.org/licenses/>
 *  
 *****************************************************************************/

#include <utopia2/bus.h>
#include <utopia2/busagent.h>

#include <QPointer>

#include <QDebug>

namespace Utopia
{

    class BusAgentPrivate
    {
    public:
        QPointer< Bus > bus;
    };




    BusAgent::BusAgent()
        : d(new BusAgentPrivate)
    {
        //qDebug() << "BusAgent()" << this;
    }

    BusAgent::~BusAgent()
    {
        //qDebug() << "~BusAgent()" << this;
        if (bus()) {
            bus()->unsubscribeFromAll(this);
        }
        delete d;
    }

    Bus * BusAgent::bus() const
    {
        return d->bus;
    }

    QString BusAgent::busId() const
    {
        return QString();
    }

    void BusAgent::resubscribeToBus()
    {}

    void BusAgent::postToBus(const QString & recipient, const QVariant & data)
    {
        if (bus()) {
            bus()->sendTo(this, recipient, data);
        }
    }

    void BusAgent::postToBus(const QVariant & data)
    {
        if (bus()) {
            bus()->send(this, data);
        }
    }

    void BusAgent::receiveFromBus(const QString & sender, const QVariant & data)
    {
        //qDebug() << "----BUS----" << sender << "->" << busId();
        //qDebug() << "-----------" << this;
        //qDebug() << "-----------" << data;
    }

    void BusAgent::setBus(Bus * newBus)
    {
        if (bus()) {
            bus()->unsubscribeFromAll(this);
        }
        d->bus = newBus;
        if (bus()) {
            resubscribeToBus();
        }
    }

    void BusAgent::subscribeToBus(const QString & sender)
    {
        if (bus()) {
            bus()->subscribeTo(this, sender);
        }
    }

    void BusAgent::subscribeToBus()
    {
        if (bus()) {
            bus()->subscribe(this);
        }
    }

    void BusAgent::subscribeToSelf()
    {
        subscribeToBus(busId());
    }

    void BusAgent::unsubscribeFromBus(const QString & sender)
    {
        if (bus()) {
            bus()->unsubscribeFrom(this, sender);
        }
    }

    void BusAgent::unsubscribeFromBus()
    {
        if (bus()) {
            bus()->unsubscribe(this);
        }
    }

    void BusAgent::unsubscribeFromSelf()
    {
        unsubscribeFromBus(busId());
    }

} // namespace Utopia
