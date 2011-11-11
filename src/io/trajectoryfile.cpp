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

#include "trajectoryfile.h"

#include <chemkit/trajectory.h>

namespace chemkit {
namespace io {

// === TrajectoryFilePrivate =============================================== //
class TrajectoryFilePrivate
{
public:
    Trajectory *trajectory;
};

// === TrajectoryFile ====================================================== //
/// \class TrajectoryFile trajectoryfile.h chemkit/trajectoryfile.h
/// \ingroup chemkit-io
/// \brief The TrajectoryFile class contains a trajectory.
///
/// The following trajectory file formats are supported in chemkit:
///     - \c xtc
///
/// \see Trajectory, TrajectoryFileFormat

// --- Construction and Destruction ---------------------------------------- //
/// Creates a new trajectory file.
TrajectoryFile::TrajectoryFile()
    : d(new TrajectoryFilePrivate)
{
    d->trajectory = 0;
}

/// Creates a new trajectory file with \p fileName.
TrajectoryFile::TrajectoryFile(const std::string &fileName)
    : GenericFile<TrajectoryFile, TrajectoryFileFormat>(fileName),
      d(new TrajectoryFilePrivate)
{
    d->trajectory = 0;
}

/// Destroys the trajectory file object.
TrajectoryFile::~TrajectoryFile()
{
    delete d->trajectory;
    delete d;
}

// --- Properties ---------------------------------------------------------- //
/// Returns \c true if the trajectory file is empty.
bool TrajectoryFile::isEmpty() const
{
    return d->trajectory == 0;
}

// --- File Contents ------------------------------------------------------- //
/// Sets the trajectory for the file to \p trajectory.
void TrajectoryFile::setTrajectory(Trajectory *trajectory)
{
    // delete current trajectory
    deleteTrajectory();

    d->trajectory = trajectory;
}

/// Returns the trajectory that the file contains.
Trajectory* TrajectoryFile::trajectory() const
{
    return d->trajectory;
}

/// Removes the trajectory from the file.
bool TrajectoryFile::removeTrajectory()
{
    if(!d->trajectory){
        return false;
    }

    d->trajectory = 0;
    return true;
}

/// Remove the trajectory from the file and deletes it.
bool TrajectoryFile::deleteTrajectory()
{
    if(!d->trajectory){
        return false;
    }

    delete d->trajectory;
    d->trajectory = 0;
    return true;
}

} // end io namespace
} // end chemkit namespace
