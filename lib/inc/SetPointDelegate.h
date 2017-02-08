/*
 * Copyright 2017 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 * 
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>
#include "ControllerMixins.h"
#include "Interface.h"
#include "RefTo.h"

class SetPointDelegate :
    public virtual SetPoint,
    public SetPointDelegateMixin
{
public:
    SetPointDelegate() = default;
    SetPointDelegate(std::function<Interface * ()> lookup) {
        setpoint.setLookup(lookup);
    }
    virtual ~SetPointDelegate() = default;


    void setLookup(std::function<Interface* ()> lookup) {
        setpoint.setLookup(lookup);
    }

    void unsetLookup() {
        setpoint.setLookup(nullptr);
    }

    std::function<Interface * ()> getLookup() {
        return setpoint.getLookup();
    }

    void accept(VisitorBase & v) final {
        v.visit(*this);
    }


    temp_t read() const final {
        return setpoint().read();
    }

    void write(temp_t val) final {
        setpoint().write(val);
    }

private:
    RefTo<SetPoint> setpoint;

    friend class SetPointDelegateMixin;
};