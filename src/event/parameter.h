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

#include <string>
#include <any>

#include "../tools/api.h"

namespace gst::event
{
  class parameter
  {
  public:
    parameter() = default;
    explicit parameter(const std::any& data) : m_data(data) {}
    explicit parameter(std::any&& data) : m_data{std::move(data)} {}

    parameter(const std::string& name, const std::string& description, const std::any& data = {})
      : m_data(data)
      , m_name(name)
      , m_description(description) {}

    virtual ~parameter() = default;

    parameter(const parameter& Other)
      : m_data{Other.m_data}
      , m_name{Other.m_name}
      , m_description{Other.m_description} {}

    parameter(parameter&& Other) noexcept
      : m_data{std::move(Other.m_data)}
      , m_name{std::move(Other.m_name)}
      , m_description{std::move(Other.m_description)} {}

    parameter& operator=(const parameter& Other)
    {
      if (this == &Other)
        return *this;
      m_data = Other.m_data;
      m_name = Other.m_name;
      m_description = Other.m_description;
      return *this;
    }

    parameter& operator=(parameter&& Other) noexcept
    {
      if (this == &Other)
        return *this;
      m_data = std::move(Other.m_data);
      m_name = std::move(Other.m_name);
      m_description = std::move(Other.m_description);
      return *this;
    }

    parameter& operator =(std::any&& data)
    {
      m_data = std::move(data);
      return *this;
    }

    parameter& operator =(const std::any& data)
    {
      m_data = data;
      return *this;
    }

    const std::any& data() const { return m_data; }
    const std::string& name() const { return m_name; }
    const std::string& description() const { return m_description; }

  private:
    std::any m_data;
    std::string m_name;
    std::string m_description;
  };
}
