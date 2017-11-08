/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Walter Julius Hennecke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#pragma once

#include <map>
#include <initializer_list>
#include <cinttypes>
#include <any>

#include "../tools/api.h"
#include "parameter.h"

namespace gst::event
{
  class qevent
  {
  public:
    typedef uint64_t event_id;
    typedef uint64_t target_id;

    explicit qevent(event_id evID, target_id targetID = 0, const std::initializer_list<std::pair<std::string, parameter>>& parameters = std::initializer_list<std::pair<std::string, parameter>>())
      : m_eventID(evID)
      , m_targetID(targetID)
    {
      for (const auto& pair : parameters)
      {
        m_parameters.insert(pair);
      }
    }

    qevent(const qevent& Other)
      : m_parameters{Other.m_parameters}
      , m_eventID{Other.m_eventID}
      , m_targetID{Other.m_targetID}
      , m_name{Other.m_name}
      , m_description{Other.m_description} {}

    qevent(qevent&& Other) noexcept
      : m_parameters{std::move(Other.m_parameters)}
      , m_eventID{Other.m_eventID}
      , m_targetID{Other.m_targetID}
      , m_name{std::move(Other.m_name)}
      , m_description{std::move(Other.m_description)} {}

    qevent& operator=(const qevent& Other)
    {
      if (this == &Other)
        return *this;
      m_parameters = Other.m_parameters;
      m_eventID = Other.m_eventID;
      m_targetID = Other.m_targetID;
      m_name = Other.m_name;
      m_description = Other.m_description;
      return *this;
    }

    qevent& operator=(qevent&& Other) noexcept
    {
      if (this == &Other)
        return *this;
      m_parameters = std::move(Other.m_parameters);
      m_eventID = Other.m_eventID;
      m_targetID = Other.m_targetID;
      m_name = std::move(Other.m_name);
      m_description = std::move(Other.m_description);
      return *this;
    }

    event_id eventID() const { return m_eventID; }
    target_id targetID() const { return m_targetID; }

    void setParameter(const std::string& name, const std::any& data)
    {
      if (name.empty())
        return;

      m_parameters[name] = data;
    }

    template <typename T>
    T param(const char* name) const
    {
      std::string sname(name);

      return std::any_cast<T>(m_parameters.at(sname).data());
    }

    template <typename T>
    T param(const std::string& name) const
    {
      return std::any_cast<T>(m_parameters.at(name).data());
    }

    const std::string& name() const { return m_name; }
    const std::string& description() const { return m_description; }

  private:
    std::map<std::string, parameter> m_parameters;
    event_id m_eventID;
    target_id m_targetID;
    std::string m_name;
    std::string m_description;
  };
}
