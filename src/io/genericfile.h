/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#ifndef CHEMKIT_GENERICFILE_H
#define CHEMKIT_GENERICFILE_H

#include "io.h"

#include <map>
#include <string>
#include <vector>
#include <istream>
#include <ostream>

#include <boost/iostreams/device/mapped_file.hpp>

#include <chemkit/variant.h>
#include <chemkit/variantmap.h>

namespace chemkit {

template<typename File, typename Format>
class GenericFile
{
public:
    // construction and destruction
    GenericFile();
    GenericFile(const std::string &fileName);
    virtual ~GenericFile();

    // properties
    void setFileName(const std::string &fileName);
    std::string fileName() const;
    void setFormat(Format *format);
    bool setFormat(const std::string &formatName);
    Format* format() const;
    std::string formatName() const;
    bool setCompressionFormat(const std::string &name);
    std::string compressionFormat() const;

    // input and output
    bool read();
    bool read(const std::string &fileName);
    bool read(const std::string &fileName, const std::string &formatName);
    bool read(std::istream &input, const std::string &formatName);
    bool read(std::istream &input);
    bool read(const boost::iostreams::mapped_file_source &input, const std::string &formatName);
    bool read(const boost::iostreams::mapped_file_source &input);
    bool write();
    bool write(const std::string &fileName);
    bool write(const std::string &fileName, const std::string &formatName);
    bool write(std::ostream &output, const std::string &formatName);
    bool write(std::ostream &output);
    bool write(std::ostream &output, Format *format);

    // file data
    void setData(const std::string &name, const Variant &value);
    Variant data(const std::string &name) const;

    // error handling
    std::string errorString() const;

    // internal methods
    bool _readFromString(const std::string &string);

    // static methods
    static std::vector<std::string> formats();
    static std::vector<std::string> compressionFormats();

protected:
    void setErrorString(const std::string &errorString);

private:
    std::string suffix(const std::string &fileName);

private:
    Format *m_format;
    std::string m_fileName;
    std::string m_errorString;
    std::string m_compressionFormat;
    VariantMap m_data;
};

} // end chemkit namespace

#include "genericfile-inline.h"

#endif // CHEMKIT_GENERICFILE_H
