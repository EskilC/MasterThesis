/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

	adsorptionArrheniusReactionRateI.H
\*---------------------------------------------------------------------------*/
#include "volFields.H"
#include "mathematicalConstants.H"
#include "thermodynamicConstants.H"

using namespace Foam::constant::mathematical;
using namespace Foam::constant::thermodynamic;
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::adsorptionArrheniusReactionRate::adsorptionArrheniusReactionRate
(
    const speciesTable& st,
    const objectRegistry& ob,
    const dictionary& dict
)
:
    ArrheniusReactionRate(st, dict),
    aName_(dict.lookup("a")),
	aField_
    (
        ob.lookupObject<volScalarField::Internal>(aName_)
    ),
	adsMax_(dict.lookupOrDefault<scalar>("adsMax",1)),
	adsoName_(dict.lookup("adso")),
	adsoField_
    (
        ob.lookupObject<volScalarField>(adsoName_)
    ),
	adsorbentName_(dict.lookup("adsorbent")),
	adsorbentField_
    (
        ob.lookupObject<volScalarField>(adsorbentName_)
    )
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::adsorptionArrheniusReactionRate::operator()
(
    const scalar p,
    const scalar T,
    const scalarField& c,
    const label li
) const
{
	
	scalar M = 1 - (((adsoField_[li]*pow(10,6))/(adsorbentField_[li]+VSMALL))/adsMax_);

    return ArrheniusReactionRate::operator()(p, T, c, li)*aField_[li]*(M);
}


inline Foam::scalar Foam::adsorptionArrheniusReactionRate::ddT
(
    const scalar p,
    const scalar T,
    const scalarField& c,
    const label li
) const
{
	//scalar M = 1 - (((adsoField_[li]*1e6)/(adsorbentField_[li]))/adsMax_);
	scalar M = 1 - (((adsoField_[li]*pow(10,6))/(adsorbentField_[li]+VSMALL))/adsMax_);
    return ArrheniusReactionRate::ddT(p, T, c, li)*aField_[li]*(M);
}


inline void Foam::adsorptionArrheniusReactionRate::write(Ostream& os) const
{
    ArrheniusReactionRate::write(os);
    writeEntry(os, "a", aName_);
	writeEntry(os, "adsMax", adsMax_);
}


inline Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const adsorptionArrheniusReactionRate& arr
)
{
    arr.write(os);
    return os;
}


// ************************************************************************* //
