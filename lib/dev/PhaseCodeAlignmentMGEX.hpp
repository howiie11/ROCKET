#pragma ident "$Id$"

/**
 * @file PhaseCodeAlignmentMGEX.hpp
 * This class aligns phase with code measurements.
 */

#ifndef GPSTK_PHASECODEALIGNMENTMGEX_HPP
#define GPSTK_PHASECODEALIGNMENTMGEX_HPP

//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2.1 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  Dagoberto Salazar - gAGE ( http://www.gage.es ). 2008, 2009, 2011
//
//============================================================================



#include "ProcessingClass.hpp"



namespace gpstk
{

      /** @addtogroup GPSsolutions */
      //@{


      /** This class aligns phase with code measurements.
       *
       * This class is meant to be used with the GNSS data structures objects
       * found in "DataStructures" class.
       *
       * A typical way to use this class follows:
       *
       * @code
       *      // INITIALIZATION PART
       *
       *      // EBRE station nominal position
       *   Position nominalPos(4833520.192, 41537.1043, 4147461.560);
       *   RinexObsStream rin("ebre0300.02o");  // Data stream
       *
       *      // Load all the SP3 ephemerides files
       *   SP3EphemerisStore SP3EphList;
       *   SP3EphList.loadFile("igs11512.sp3");
       *   SP3EphList.loadFile("igs11513.sp3");
       *   SP3EphList.loadFile("igs11514.sp3");
       *
       *      // More declarations here: ComputeMOPSWeights, SimpleFilter,
       *      // LICSDetector, MWCSDetector, SolidTides, OceanLoading,
       *      // PoleTides, CorrectObservables, ComputeWindUp, ComputeLinear,
       *      // LinearCombinations, SolverPPP, etc...
       *
       *      // Object to align phase (LC) with code (PC) measurements
       *   PhaseCodeAlignmentMGEX phaseAlign;
       *
       *     // PROCESSING PART
       *
       *   gnssRinex gRin;
       *
       *   while(rin >> gRin)
       *   {
       *      try
       *      {
       *         gRin  >> basicM
       *               >> correctObs
       *               >> compWindup
       *               >> computeTropo
       *               >> linear
       *               >> pcFilter
       *               >> markCSLI
       *               >> markCSMW
       *               >> markArc
       *               >> phaseAlign
       *               >> pppSolver;
       *      }
       *      catch(...)
       *      {
       *         cerr << "Unknown exception at epoch: " << time << endl;
       *         continue;
       *      }
       *
       *         // Print results
       *      cout << time.DOYsecond()      << "  "; // Output field #1
       *      cout << pppSolver.solution[1] << "  "; // dx: Output field #2
       *      cout << pppSolver.solution[2] << "  "; // dy: Output field #3
       *      cout << pppSolver.solution[3] << "  "; // dz: Output field #4
       *      cout << pppSolver.solution[0] << "  "; // wetTropo: Out field #5
       *      cout << endl;
       *   }
       * @endcode
       *
       * The "PhaseCodeAlignmentMGEX" object will visit every satellite in the GNSS
       * data structure that is "gRin" and, if an arc change or cycle slip has
       * happened, it will compute a phase offset in order to take the phase
       * measurement close to the corresponding code measurement.
       *
       * By default, "PhaseCodeAlignmentMGEX" objects will align the
       * ionosphere-free phase combination (LC) with the corresponding code
       * (PC). Also, it will check changes in satellite arcs in order to know
       * when offset recomputing is necessary. All these defaults may be
       * changed with the appropriate methods.
       *
       * The use of this class is not mandatory; however, it is recommendable
       * given that resulting phase ambiguities are smaller, and it
       * potentially improves the numerical stability of the solver.
       *
       * \warning Be aware that if you change the phase/code pair, you must
       * change the wavelength accordingly.
       *
       * \warning Objects in this class store their internal state, so you
       * MUST NOT use the SAME object to process DIFFERENT data streams.
       *
       * @sa SatArcMarker.hpp, LICSDetector.hpp and MWCSDetector.hpp.
       *
       */
   class PhaseCodeAlignmentMGEX : public ProcessingClass
   {
      public:

         /// Default constructor.
      PhaseCodeAlignmentMGEX()
         : satSystem( SatID::systemGPS ),
			  phaseType(TypeID::LC), codeType(TypeID::PC),
           phaseWavelength(0.1069533781421467), useSatArcs(true),
           watchCSFlag(TypeID::CSL1)
      { };


         /** Common constructor
          *
          * @param phase            Phase TypeID.
          * @param code             Code TypeID.
          * @param wavelength       Phase wavelength, in meters.
          * @param useArc           Whether satellite arcs will be used or not.
          */
      PhaseCodeAlignmentMGEX( const TypeID& phase,
                          const TypeID& code,
                          const double wavelength,
                          bool useArc = true );


         /// Method to get the phase TypeID being used.
      virtual TypeID getPhaseType() const
      { return phaseType; };

         /** Method to set the sat syatem to be used.
          *
          * @param phase            sat system.
          */
      virtual PhaseCodeAlignmentMGEX& setSatSystem(
										const SatID::SatelliteSystem& sys )
      { satSystem = sys; return (*this); };



         /** Method to set the phase TypeID to be used.
          *
          * @param phase            Phase TypeID.
          */
      virtual PhaseCodeAlignmentMGEX& setPhaseType(const TypeID& phase)
      { phaseType = phase; return (*this); };


         /// Method to get the code TypeID being used.
      virtual TypeID getCodeType() const
      { return codeType; };


         /** Method to set the code TypeID to be used.
          *
          * @param code             Code TypeID.
          */
      virtual PhaseCodeAlignmentMGEX& setCodeType(const TypeID& code)
      { codeType = code; return (*this); };


         /// Method to get phase wavelength being used.
      virtual double getPhaseWavelength() const
      { return phaseWavelength; };


         /** Method to set the phase wavelength to be used.
          *
          * @param wavelength       Phase wavelength, in meters.
          */
      virtual PhaseCodeAlignmentMGEX& setPhaseWavelength(double wavelength);


         /// Method to get if this class will use satellite arcs (true) or
         /// cycle slip flags (false).
      virtual bool getUseSatArc() const
      { return useSatArcs; };


         /** Method to set if this class will use satellite arcs (true) or
          *  cycle slip flags (false).
          *
          * @param useArc           Whether this class will use satellite arcs
          *                         (true) or cycle slip flags (false).
          */
      virtual PhaseCodeAlignmentMGEX& setUseSatArc(bool useArc)
      { useSatArcs = useArc; return (*this); };


         /// Method to get the default CS flag type being used.
      virtual TypeID getCSFlag() const
      { return watchCSFlag; };


         /** Method to set the default CS flag type to be used.
          *
          * @param watchFlag     Cycle slip flag to be watched.
          */
      virtual PhaseCodeAlignmentMGEX& setCSFlag(const TypeID& watchFlag)
      { watchCSFlag = watchFlag; return (*this); };


         /** Returns a satTypeValueMap object, adding the new data generated
          *  when calling this object.
          *
          * @param epoch     Time of observations.
          * @param gData     Data object holding the data.
          */
      virtual satTypeValueMap& Process( const CommonTime& epoch,
                                        satTypeValueMap& gData )
         throw(ProcessingException);


         /** Returns a gnnsSatTypeValue object, adding the new data generated
          *  when calling this object.
          *
          * @param gData    Data object holding the data.
          */
      virtual gnssSatTypeValue& Process(gnssSatTypeValue& gData)
         throw(ProcessingException);


         /** Returns a gnnsRinex object, adding the new data generated when
          *  calling this object.
          *
          * @param gData    Data object holding the data.
          */
      virtual gnssRinex& Process(gnssRinex& gData)
         throw(ProcessingException);


         /// Returns a string identifying this object.
      virtual std::string getClassName(void) const;


         /// Destructor
      virtual ~PhaseCodeAlignmentMGEX() {};


   private:


			/// Sat system 
		SatID::SatelliteSystem satSystem;

         /// TypeID of phase measurement.
      TypeID phaseType;


         /// TypeID of code measurement.
      TypeID codeType;


         /// Wavelength of phase measurement.
      double phaseWavelength;


         /** Flag indicating if this class will watch for satellite arcs (true)
          *  or cycle slip flags (false).
          */
      bool useSatArcs;


         /// If field 'useSatArcs' is false, cycle slip flag to be watched.
      TypeID watchCSFlag;


         /// Structure used to store SV alignment data.
      struct alignData
      {
            // Default constructor initializing the data in the structure
         alignData() : arcNumber(0.0), offset(0.0) {};

         double arcNumber;       ///< Current arc number
         double offset;          ///< Offset value to be applied
      };


         /// Map holding the information regarding every satellite
      std::map<SatID, alignData> svData;


   }; // End of class 'PhaseCodeAlignmentMGEX'

      //@}

}  // End of namespace gpstk

#endif   // GPSTK_PHASECODEALIGNMENT_HPP
