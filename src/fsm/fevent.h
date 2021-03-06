/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Walter Julius Hennecke
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
#include <any>
#include <utility>
namespace gst::fsm
{
  /**
   * @brief Event id.
   */
  typedef unsigned long event_id;

  /**
   * @brief A event for the finite state mashine.
   */
  class fevent
  {
  public:
    /**
     * @brief Constructor.
     * @param id The event id.
     * @param parameters Optional parameters.
     */
    explicit fevent(event_id id = 0, std::map<std::string, std::any> parameters = {})
      : m_parameters(std::move(parameters))
      , m_id(id) { }

    /**
     * @brief Copy constructor.
     * @param other Object to copy.
     */
    fevent(const fevent& other) = default;

    /**
     * @brief Destructor.
     */
    virtual ~fevent() = default;

    /**
     * @brief Assignment operator.
     * @param other Object to assign.
     * @return This object.
     */
    fevent& operator =(const fevent& other) = default;

    /**
     * @brief Get the event id.
     * @return Event id.
     */
    event_id id() const
    {
      return m_id;
    }

    /**
     * @brief Modify an existing or add a new parameter.
     * @param name Parameter name.
     * @param data Parameter data.
     */
    void setParameter(const std::string& name, const std::any& data);

    /**
     * @brief Extract the value for a parameter.
     * @param name Parameter name.
     * @return Converted parameter.
     */
    template <typename T>
    T parameter(const char* name) const
    {
      std::string sname(name);

      return std::any_cast<T>(m_parameters.at(sname));
    }

    /**
     * @brief Extract the value for a parameter.
     * @param name Parameter name.
     * @return Converted parameter.
     */
    template <typename T>
    T parameter(const std::string& name) const
    {
      return std::any_cast<T>(m_parameters.at(name));
    }

  private:
    std::map<std::string, std::any> m_parameters;
    event_id m_id;
  };
}
