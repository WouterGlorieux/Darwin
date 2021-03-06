//============================================================================
// Name        : SteadyStateTokamak.cpp
// Author      : Skidzobolder
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <String>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

/*
 * class ObservableDbl
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//package observable;

//import java.util.Observable;

/**
 * Observable mechanism for a double variable. Adapted from
 * Listing 21.14 of "Special Edition, Using Java". Added the
 * maximum and minimum features.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 1999/11/15 20:37:49 $.
 * @author Daren Stotler
 * @see ObservableTest
 */

/*
 * $Log: ObservableDbl.java,v $
 * Revision 1.1.1.1  1999/11/15 20:37:49  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 1.0 02-24-97 Finally give it a number.
 *
 * This implementation closely follows that of ObservableInt in
 * the "Special Edition, Using Java" book. The maximum and minimum
 * features proved desirable when used in conjunction with sliders
 * and with variables having a well-defined range.
 */
class ObservableDbl /*extends Observable*/ {
private :
	double value_, max_, min_;

  /**
   * Simplest constructor with a default value initialization.
   */
public :
	ObservableDbl() {
    value_ = 0.;            // Default
  }

  /**
   * Initializes the class instance with a specified value for
   * the observable double.
   * @param new_value initial value
   */
  ObservableDbl(double new_value) {
    value_ = new_value;
  }

  /**
   * Call this method to change the value of the observable.
   * Observers will be notified of the change.
   * @param new_value altered value for double.
   */
  void setValue(double new_value) {
    /*
     * Be sure the value really is changing...
     */
    if (new_value != value_) {
      value_ = new_value;
      //setChanged();
      //notifyObservers();
    }
  }

  /**
   * Get the current value of the observable.
   */
  double getValue() {
    return value_;
  }

  /**
   * Set the maximum allowed value for the ObservableDbl.
   * @param m maximum value
   */
  void setMaximum(double m) {
    max_ = m;
  }

  /**
   * Get the maximum allowed value for the ObservableDbl.
   */
  double getMaximum() {
    return max_;
  }

  /**
   * Set the minimum allowed value for the ObservableDbl.
   * @param m minimum value
   */
  void setMinimum(double m) {
    min_ = m;
  }

  /**
   * Get the minimum allowed value for the ObservableDbl.
   */
  double getMinimum() {
    return min_;
  }
};


/*
 * class ObservableRatio
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//package observable;

//import java.util.Observer;
//import java.util.Observable;

/**
 * This rather neat class uses allows a relationship (here, a ratio) to
 * be maintained between two Observable doubles. When either of the two
 * changes, the other is modified to maintain the ratio between them.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 1999/11/15 20:37:49 $.
 * @author Daren Stotler
 * @see ObservableDbl
 */

/*
 * $Log: ObservableRatio.java,v $
 * Revision 1.1.1.1  1999/11/15 20:37:49  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 1.0 02-24-97 Finally give it a number.
 *
 * Implementation really hasn't changed since its original form.
 * The initial application envisioned was for correlating the
 * toroidal plasma current and magnetic field in a tokamak; the
 * ratio of the two can be specified in terms of the safety factor, q.
 */
class ObservableRatio /*implements Observer */{

private :
   ObservableDbl valueOne_, valueTwo_;
   double ratio_;

  /**
   * The constructor requires not only the names of the two ObservableDbl's,
   * but also their ratio.
   * @param od1 first ObservableDbl
   * @param od2 second ObservableDbl
   * @param r ratio of the first ObservableDbl to the second
   */
public :
   ObservableRatio(ObservableDbl od1, ObservableDbl od2, double r) {
    valueOne_ = od1;
    //valueOne_.addObserver(this);

    valueTwo_ = od2;
    //valueTwo_.addObserver(this);

    ratio_ = r;    // ratio_ == valueOne_ / valueTwo_

    if (valueOne_.getValue() == 0. && valueTwo_.getValue() != 0.) {
      valueOne_.setValue(ratio_*valueTwo_.getValue());
    }
    if (valueTwo_.getValue() == 0. && valueOne_.getValue() != 0.) {
      valueTwo_.setValue(valueOne_.getValue() / ratio_);
    }

    //std::cout << "valueOne: " << valueOne_.getValue() << std::endl;
    //std::cout << "valueTwo: " << valueTwo_.getValue() << std::endl;
  }
  /**
   * This method watches a change in one of the two ObservableDbl's
   * and then updates the other. Note: this will probably get called
   * twice with each change. The second call will have no effect.
   */
/*  void update(ObservableDbl obs) {
    if (obs == valueOne_) {
      valueTwo_.setValue(valueOne_.getValue() / ratio_);
    }
    if (obs == valueTwo_) {
      valueOne_.setValue(ratio_ * valueTwo_.getValue());
    }
  }
*/
};





/*
 * class ExpTauE
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//package ssfd;

//import java.lang.Math;

/**
 * Uses a standard power law expression for the energy confinement time.
 * The exponents are specified at instantiation. The resulting
 * expression can then be evaluated for when a set of global plasma
 * parameters is provided.
 *
 * There is also a <a href="http://w3.pppl.gov/~dstotler/SystemsCode/">
 * User's Manual</a> for the
 * full-featured FORTRAN code upon which this code is based.
 * The corresponding equation numbers are mentioned in the code below.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 1999/11/15 20:37:49 $.
 * @author Daren Stotler
 */

/*
 * $Log: ExpTauE.java,v $
 * Revision 1.1.1.1  1999/11/15 20:37:49  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 1.0 02-13-97 Finally give it a number.
 *
 * This is a simple and obvious class. It hasn't changed since the initial
 * implementation.
 */
class ExpTauE {

  /*
   * The constructor stores the overall coefficient and 8 exponents
   * which comprise the power law fit expression in this array, Eq. 42.
   */
private :
	double txp_[9];// = new double [9];

  /**
   * Defines a scaling expression for the energy confinement time.
   * @param const overall multiplicative constant
   * @param massExp exponent on the average ion mass
   * @param elongationExp exponent on the plasma elongation
   * @param currentExp exponent on the plasma current
   * @param densityExp exponent on the line-averaged electron density
   * @param bfieldExp exponent on the toroidal magnetic field
   * @param rminorExp exponent on the plasma minor radius
   * @param rmajorExp exponent on the plasma major radius
   * @param pinputExp exponent on the net plasma input power
   */
public :
	ExpTauE(){}

	ExpTauE(double constant, double mass_exp, double elongation_exp,
          double current_exp, double density_exp, double bfield_exp,
          double rminor_exp, double rmajor_exp, double pinput_exp)
    {
      txp_[0] = constant;
      txp_[1] = mass_exp;
      txp_[2] = elongation_exp;
      txp_[3] = current_exp;
      txp_[4] = density_exp;
      txp_[5] = bfield_exp;
      txp_[6] = rminor_exp;
      txp_[7] = rmajor_exp;
      txp_[8] = pinput_exp;
    }

  /**
   * Evaluate the scaling expression for the energy confinement time.
   * @param aibar average ion mass (amu)
   * @param elongation the plasma elongation (dimensionless)
   * @param current plasma current (in amps)
   * @param density line-averaged electron density (in m**-3)
   * @param bfield toroidal magnetic field (in tesla)
   * @param rminor plasma minor radius (in m)
   * @param rmajor plasma major radius (in m)
   * @param pinput net input power to the plasma (in watts)
   * @return energy confinement time in seconds
   */
  double calcExpTauE(double aibar, double elongation, double current,
                            double density, double bfield, double rminor,
                            double rmajor, double pinput)
    {
      double ztaue = txp_[0]
        * pow(aibar,txp_[1])
        * pow(elongation,txp_[2])
        * pow(current*1.e-6,txp_[3])
        * pow(density*1.e-19,txp_[4])
        * pow(bfield,txp_[5])
        * pow(rminor,txp_[6])
        * pow(rmajor,txp_[7])
        * pow(max(pinput*1.e-6,1.),txp_[8]); // Note minimum value!

      return (ztaue);
    }
};






/*
 * class FusionReactor
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//package ssfd;

//import java.lang.Math;
//import observable.ObservableDbl;
//import observable.ObservableRatio;

/**
 * The instance variables of this class specify the parameters of a
 * hypothetical fusion reactor. The class is largely comprised of
 * methods for evaluating the principle energy source and sink terms
 * in the reactor.
 *
 * There is also a <a href="http://w3.pppl.gov/~dstotler/SystemsCode/">
 * User's Manual</a> for the
 * full-featured FORTRAN code upon which this code is based.
 * The corresponding equation numbers are mentioned in the code.
 *
 * @version $Revision: 1.2 $, $Date: 2000/01/21 20:39:39 $.
 * @author Daren Stotler
 * @see ExpTauE
 */

/*
 * $Log: FusionReactor.java,v $
 * Revision 1.2  2000/01/21 20:39:39  dstotler
 * Changed energy confinement time multiplier from 1.85 to 1.80.
 *
 * Revision 1.1.1.1  1999/11/15 20:37:49  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 1.0 02-06-97 Finally give it a number.
 *
 * The methods in this class have changed little since the initial
 * implementation taken from the ASPECT code, apart from the introduction
 * of Observables.
 */
class FusionReactor {

public :
  /*
   * Observable variables which provide the methods of information transfer
   * from and to other classes.
   */
  ObservableDbl oBField_, oCurrent_, oDensity_, oPaux_, oTemperature_,
                        oScore_;

  /*
   * These can in general be adjusted, but here we hold 'em fixed for
   * the life of the object.
   */
  double rMinor_, rMajor_, qCyl_;
  double elongation_, zEff_, zImp_, rnDnDT_, cTau_;     // Local inputs
  double volume_, xSArea_, rnDTne_, rnine_, rnZne_;     // Derived

  /*
   * Expression for the auxiliary-heated energy confinement time.
   */
  ExpTauE tauEForm_;

  /*
   * Constants
   */
  double K_BOLTZMANN;// = 1.6021e-16; // Boltzmann's constant
  double MU_0;// = 4.0e-7 * Math.PI;  // Permittivity
  double E_ALPHA_0;// = 3.5e3;        // Alpha energy (keV)

  /**
   * Constructs and initializes a hypothetical fusion reactor with
   * the specified parameters:
   * @param a plasma minor radius in meters
   * @param R plasma major radius in meters
   * @param q equivalent cylindrical safety factor
   * @param bf (observable) toroidal magnetic field in tesla
   * @param de (observable) electron density in m**-3
   * @param pa (observable) auxiliary heating power in mega-watts
   * @param te (observable) electron = ion temperature in 1.e6 K
   * @param bq (observable; output) measure of reactor performance
   * @param t expression for the auxiliary heated confinement time
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid
   */

//public :
  FusionReactor(){}

  FusionReactor(double a, double R, double q,
		       ObservableDbl bf, ObservableDbl de, ObservableDbl pa,
		       ObservableDbl te, ObservableDbl bq,
		       ExpTauE t) /*throws IncompleteReactorExcpn*/ {

			 rMinor_ = a;
			 rMajor_ = R;
			 qCyl_ = q;
			 tauEForm_ = t;

			 oBField_ = bf;
			 oDensity_ = de;
			 oPaux_ = pa;
			 oTemperature_ = te;

			// std::cout << "temperature: "<< oTemperature_.getValue() << std::endl;
			 oScore_ = bq;

			 init();
		       }

  /**
   * Hardwire some of the remaining variables; computed derived
   * quantities. Check inputs as well.
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid.
   */
   void init() /*throws IncompleteReactorExcpn*/ {

	   K_BOLTZMANN = 1.6021e-16; // Boltzmann's constant
	   MU_0 = 4.0e-7 * M_PI;  // Permittivity
	   E_ALPHA_0 = 3.5e3;        // Alpha energy (keV)

    /*
     * The present implementation assumes purely elliptical
     * cross sections. Values are again for BPX.
     */
    elongation_ = 2.0;
    zEff_ = 1.65;       // Z-effective
    zImp_ = 6.0;        // Z of dominant impurity
    rnDnDT_ = 0.5;      // deuterium / (deuterium + tritium) ratio
    cTau_ = 1.80;       // Confinement enhancement multiplier

    if (rMinor_ <= 0.)
      throw /*new IncompleteReactorExcpn(*/"rMinor_ nonpositive: " /*+ rMinor_)*/;
    if (rMajor_ <= 0.)
      throw /*new IncompleteReactorExcpn(*/"rMajor_ nonpositive: "/* + rMajor_)*/;
    if (elongation_ <= 0.)
      throw /*new IncompleteReactorExcpn(*/"elongation_ nonpositive: "/* +elongation_)*/;
    if (zEff_ <= 0.)
      throw /*new IncompleteReactorExcpn(*/"zEff_ nonpositive: "/* + zEff_)*/;

    /*
     * With elliptical cross sections, area and volume expressions
     * are trivial.
     */
    xSArea_ = M_PI*rMinor_*rMinor_*elongation_;
    volume_ = 2.*M_PI*rMajor_*xSArea_;

    /*
     * Calculate density ratios, Eqs. 54 - 56
     */
    rnDTne_ = (zImp_ - zEff_) / (zImp_ - 1.);
    rnZne_ = (zEff_ - rnDTne_) / (zImp_ * zImp_);
    rnine_ = rnDTne_ + rnZne_;                       // Ion / electron density

    /*
     * Since qCyl_ varies much less from one reactor design to
     * another than do the magnetic field or plasma current,
     * we hold qCyl_ fixed and compute either the current or
     * field from it using the ObservableRatio, b_c_ratio.
     * Now set up to read the field and set the current.
     */
    oCurrent_ = ObservableDbl(0.);
    double b_c_ratio = qCyl_ * 1.e6 * MU_0 * rMajor_   // = bfield / current
      / (M_PI * rMinor_*rMinor_ * (1. + elongation_*elongation_));

    //std::cout << "bla "<< oBField_.getValue() << std::endl;
    /*ObservableRatio o_b_o_c =*/ ObservableRatio(oBField_, oCurrent_, b_c_ratio);

    if (oBField_.getValue() == 0. && oCurrent_.getValue() != 0.) {
    	oBField_.setValue(b_c_ratio*oCurrent_.getValue());
    }
    if (oCurrent_.getValue() == 0. && oBField_.getValue() != 0.) {
    	oCurrent_.setValue(oBField_.getValue() / b_c_ratio);
    }


    //std::cout << "oCurrent: " << oCurrent_.getValue() << std::endl;
  }

  void setTemperature(double temperature){
	  oTemperature_.setValue(temperature);
  }

  double getTemperature(){
	 return  oTemperature_.getValue();
  }

  /**
   * Calculate the fusion power released in the form of energetic alpha
   * particles.
   * @return fusion alpha power in watts
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid.
   */
  double calcPalpha() /*throws IncompleteReactorExcpn */{

    /*
     * The following are implemented with limiting values of the form factors,
     * assuming flat profiles. Hence, the variables "density" and "temperature"
     * are synonymous with both average and central values. Incorporation of
     * profile effects should be done with care referring to the original code.
     */
    double density = oDensity_.getValue() * 1.e20;           // in m**-3
    double temperature = oTemperature_.getValue() / 11.604;  // in keV

    if (density <= 0.)
      throw /*new IncompleteReactorExcpn(*/"density nonpositive: " /*+ density)*/;


    if (temperature <= 0.)
      throw /*new IncompleteReactorExcpn(*/"temperature nonpositve: "/*+temperature)*/;
   // std::cout << "temp check done" << std::endl;

    /*
     * DT reaction rate formula from L. M. Hively, Nucl. Fusion 17, 873 (1977).
     */
    double za1, za2, za3, za4, za5, za6, zrsg;
    za1=-21.377692;
    za2=-25.204054;
    za3=-7.1013427e-2;
    za4=1.9375451e-4;
    za5=4.9246592e-6;
    za6=-3.9836572e-8;
    zrsg=.2935;

    /*
     * Note the careful placement of the 1.e20 factors (from den20, below)
     * so as to reduce the chances for overflow or underflow. The 1.e-6
     * factor puts the reaction rate itself in units of m**3/s.
     */
    double formula = 1.e20 * exp(za1 / pow(temperature,zrsg) + za2
				+ temperature*(za3 + temperature*(za4
				      + temperature*(za5 + temperature*za6))))
	              * 1.e20 * 1.e-6;
    double den20 = rnDTne_ * density / 1.e20;

    return (E_ALPHA_0 * K_BOLTZMANN * rnDnDT_ * (1. - rnDnDT_) * den20 * den20
            * formula * volume_);
  }

  /**
   * Calculate the resistive, Ohmic heating of the plasma by the
   * toroidal current.
   * @return ohmic heating power in watts
   */
  double calcPoh() {

    double density = oDensity_.getValue() * 1.e20;           // in m**-3
    double temperature = oTemperature_.getValue() / 11.604;  // in keV
    double current = oCurrent_.getValue() * 1.e6;            // in Amps

    /*
     * Coulomb log from nrl formulary converted to MKS-keV, Eq. 25
     */
    double zcolam = 37.8 - log(sqrt(density)/temperature);

    /*
     * Formulation from Eq. 24 is consistent with Uckan, Fusion Tech. 14,
     * 299 (1988).
     */
    double zj0 = current / xSArea_;   // Central current density, Eq. 26
    double resnc = 2.5;              // Neoclassical resistivity correction
    double fpoh = 1.65e-9 * zEff_ * zcolam * resnc
      * pow(temperature,-1.5) * zj0 * zj0 * volume_;

    return (fpoh);
  }

  /**
   * Calculate total radiated power lost from the plasma.
   * @return radiated power in watts
   */
  double calcPrad() {

    double density = oDensity_.getValue() * 1.e20;            // in m**-3
    double temperature = oTemperature_.getValue() / 11.604;   // in keV

    /*
     * Presently just include Bremsstrahlung radiation (in W), Eq. 27
     */
    double den20 = density / 1.e20;
    double fpbr = 1.0e06 * 0.0168 * den20 * den20
      * sqrt(temperature/10.) * zEff_ * volume_;

    return (fpbr);
  }

  /**
   * Uses the definition of the energy confinement time to infer the
   * amount of heat conducted out of the plasma.
   * @param pinput net heating power needed for power-degrading scalings
   * @return heat lost by conduction in watts
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid.
   */
  double calcPcon(double pinput) /*throws IncompleteReactorExcpn */{

    double current = oCurrent_.getValue() * 1.e6;           // in Amps
    double density = oDensity_.getValue() * 1.e20;          // in m**-3
    double temperature = oTemperature_.getValue() / 11.604; // in keV
    double bfield = oBField_.getValue();



    if (current <= 0.)
      throw /*new IncompleteReactorExcpn(*/"current nonpositive: "/* + current)*/;



    if (bfield <= 0.)
      throw /*new IncompleteReactorExcpn(*/"bfield nonpositive: "/* + bfield)*/;

    /*
     * Total thermal energy, Eq. 30, in joules.
     */
    double w_tot = 1.5 * density * K_BOLTZMANN * temperature
      * ( 1. + rnine_ ) * volume_;

    /*
     * Confinement time expressions:
     * ztaue   is the auxiliary heating confinement time given by instance
     *         tau of the ExpTauE class.
     * ztauNA  is the neoAlcator confinement time
     * zatuEff is the geometric mean with the multiplier cTau_ on the auxiliary
     *         heated time. In ASPECT the exponent (2) is a variable.
     * Note that aibar is hardwired to 2.5
     */
    double tau_e = tauEForm_.calcExpTauE(2.5, elongation_, current, density,
                                        bfield, rMinor_, rMajor_, pinput);

    double tau_na = 7.e-22 * density * rMinor_ * rMajor_ * rMajor_ * qCyl_;

    double tau_eff = 1. /
      sqrt(1./(tau_na*tau_na) + pow(cTau_ * tau_e,-2));

    return (w_tot / tau_eff);
  }

  /**
   * Evaluate the power balance and calculate the time rate of
   * change of the integrated plasma energy.
   * @return rate of change of the plasma energy
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid.
   */
  double calcdWdt()/* throws IncompleteReactorExcpn */{

	// std::cout << "temperature: " << oTemperature_.getValue() << std::endl;

    double p_alpha = calcPalpha();

    double p_oh= calcPoh();

    double p_rad = calcPrad();

    double p_aux = oPaux_.getValue() * 1.e6;    double p_input = p_alpha + p_oh + p_aux - p_rad;

    double p_con = calcPcon(p_input);



    return (p_input - p_con);

  }

  /**
   * Calculate a figure of merit.
   * This will:
   * <ol>
   * <li> be 100 at Q = fusion
   * power divided by total heating power,
   * <li> be more sensitive to changes in
   * Q at low Q than at high Q.
   * </ol>
   * This score also takes into account the
   * density and beta limits; the score = 0 when they are exceeded.
   * The score value is propagated through the rest of the code by
   * the ObservableDbl oScore_.
   * @see #calcBetaMax
   * @see #calcDenMax
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid.
   */
  int calcOScore() /*throws IncompleteReactorExcpn*/ {

   double p_alpha = calcPalpha();
    double p_oh= calcPoh();
    double p_aux = oPaux_.getValue() * 1.e6;

    double beta=0.;
    //try {
      beta = calcBetaTot();
    /*} catch (IncompleteReactorExcpn e) {
      System.out.println("performanceValue caught exception: "+e.getMessage());
      oScore_.setValue(0.);
    }*/
    double betamax = calcBetaMax();
    double denmax = calcDenMax();
    double density = oDensity_.getValue() * 1.e20;

    if (beta > betamax || density > denmax) {
   /*   System.out.println("Disruption, beta/betamax = " + beta/betamax
			 + ", density/denmax = " + density/denmax);*/
      oScore_.setValue(0.);
    }
    else {
      double q = 5.*p_alpha / (p_aux + p_oh);       // Fusion Q
      oScore_.setValue(100. * pow(q/100.,0.3));  // Ad hoc score formula
    }


    //std::cout << "SCORE: " << oScore_.getValue() << std::endl;

    return (int)(oScore_.getValue() * 100);
  }

  /**
   * Calculate the total (thermal + fast alpha) plasma beta.
   * @return ratio of the plasma to magnetic field pressure (dimensionless)
   * @exception IncompleteReactorExcpn one or more of these parameters
   *                                   is invalid.
   */
  double calcBetaTot()/* throws IncompleteReactorExcpn */{

    double density = oDensity_.getValue() * 1.e20;           // in m**-3
    double temperature = oTemperature_.getValue() / 11.604;  // in keV
    double bfield = oBField_.getValue();

    /*
     * Source rate of alpha particles.
     */
    double znsour = calcPalpha() / (E_ALPHA_0 * K_BOLTZMANN * volume_);

    /*
     * Compute electron, deuterium, tritium, and impurity Coulomb
     * logarithms, Eq. 63. The impurity mass (zamimp) is approximately
     * twice its nuclear charge.
     */
    double zlame = 37.8 - log(sqrt(density)/temperature);
    double zlamd = 45.5 + log(sqrt(temperature / density)
                                   * 4.*2./(4.+2.));
    double zlamt = 45.5 + log(sqrt(temperature / density)
                                   * 4.*3./(4.+3.));
    double zamimp = 2. * zImp_;
    double zlamz = 45.5 + log(sqrt(temperature / density)
                                     * 4.*zamimp/(4.+zamimp));

    /*
     * Critical slowing down energy at which loss of energy to electrons
     * equals the loss to ions, Eq. 62.
     */
    double zecrit = 4.0*14.8 * temperature *
      pow((((rnDnDT_ * zlamd / 2. + (1.-rnDnDT_) * zlamt / 3.) * rnDTne_
                 + rnZne_ * zlamz * zImp_*zImp_ / zamimp)
                / zlame),(2./3.));
    double zvcrat = sqrt(E_ALPHA_0 / zecrit); // Velocity ratio, Eq. 64

    double ztauth = 0.371 * pow(temperature/10.,1.5) // Slowing down
      * (1.0e20/density) * (17./zlame);                   // time, Eq. 65

    double zeavg = E_ALPHA_0*K_BOLTZMANN * 0.5 // Avg. alpha energy, Eq. 66
      * (1.- pow(zvcrat,(-2.))
         *(log((1.+ pow(zvcrat,3.))/pow((1.+zvcrat),3.)) / 3.
           + (2. * atan((2.*zvcrat - 1.) / sqrt(3.))
              + M_PI / 3.) / sqrt(3.)));

    /*
     * Time to thermalize, Eq. 67
     */
   // double ztaunf = ztauth * log( 1. + pow(zvcrat,3.) ) / 3.;

    /*
     * Alpha beta, Eq. 69; thermal beta, Eq. 61; total beta, Eq. 70;
     * alpha density, Eq. 68; alpha / electron density:
     */
    double pbetfa = (2.*MU_0/bfield*bfield)*(2./3.)*(znsour*ztauth*zeavg);
    double zbetth = (2.*MU_0/bfield*bfield)*density
      *( 1. + rnine_ )*K_BOLTZMANN*temperature;
    double pbeta  = pbetfa + zbetth;

    return(pbeta);
  }

  /**
   * Calculate maximum allowed beta value.
   * @return maximum allowed ratio of plasma to magnetic field pressure
   */
  double calcBetaMax()
    {
    double current = oCurrent_.getValue();            // in mega-amps!
    double bfield = oBField_.getValue();

    /*
     * Use the Troyon limit with a coefficient of 3.0
     */
    return (3.0 * current / (rMinor_ * bfield));
    }

  /**
   * Calculate the maximum allowed density.
   * @return maximum allowed electron density in m**-3
   */
  double calcDenMax()
    {
      double current = oCurrent_.getValue();              // in mega-amps!

      /*
       * This is the Greenwald limit; it's normally taken to
       * be the line-averaged density. But, here, we have effectively
       * flat profiles.
       */
      return (1.e20 * current / (M_PI*rMinor_*rMinor_));
    }
};

/*
 * class SteadyStateFusionReactor
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//package ssfd;

//import rootsolvers.Solved;
//import observable.ObservableDbl;

/**
 * This class takes an instance of the FusionReactor class and solves
 * for the value of the parameter Ox which yields calcdWdt = 0, i.e.,
 * steady state. The neat thing about using an ObservableDbl for the
 * solution parameter is that in principle any of the FusionReactor
 * ObservableDbl's could be used. In practice, though, only for a
 * few (at least one!) of them can one bound the root as is required
 * for the bisection technique.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 1999/11/15 20:37:50 $.
 * @author Daren Stotler
 * @see ssfd.SteadyStateFusionDemo#init
 * @see FusionReactor
 * @see ssfd.SteadyStateFusionDemo#solveReactor
 * @see Bisection
 */

/*
 * $Log: SteadyStateFusionReactor.java,v $
 * Revision 1.1.1.1  1999/11/15 20:37:50  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 1.1 01-22-98 Replace root-solvers with simpler interface approach.
 * 1.0 02-13-97 Finally give it a number.
 *
 * The methods in this class have changed little since the initial
 * implementation taken from the ASPECT code, apart from the introduction
 * of Observables.
 */
class SteadyStateFusionReactor /*implements Solved*/ {

private :
	FusionReactor* reactorSolved;
    ObservableDbl Ox;

  /**
   * Initializes the class variables corresponding to the parameters:
   * @param f instance of FusionReactor which is being solved
   * @param od variable to be used in the solution algorithm
   */
public :
    SteadyStateFusionReactor(FusionReactor* f, ObservableDbl od) {
    reactorSolved = f;
    Ox = od;
  }

  /**
   * The function being solved is essentially the time rate of change
   * of the total plasma energy, calcdWdt from the FusionReactor
   * class. Note the use of the ObservableDbl to subtly transfer the
   * root information back out. And, be aware that the
   * IncompleteReactorExcpn is being caught here, for better or worse.
   * @param x double representing the solution parameter
   * @return function value
   */
  double calcfOfX(double x) {


	//std::cout << "calcfofX: " << "x: " << x  << " "<<   reactorSolved->oCurrent_.getValue() << std::endl;


    Ox.setValue(x);
    reactorSolved->setTemperature(x);

	//std::cout << "Ox: " << Ox.getValue() << std::endl;
    double fX;
    try {

      fX = reactorSolved->calcdWdt();

    } catch (char const*) {
      //std::cout << "sSFR.calcfOfX caught exception: " << std::endl;
      return (0.);
    }
    return (fX);
  }
};



/*
 * interface Solved
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
//package rootsolvers;

/**
 * An interface which provides the function being solved to root-finding
 * algorithms. This approach to using an interface closely follows the
 * examples in Core Java 1.1, Volume 1 by Horstmann & Cornell.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 1999/11/15 20:37:49 $.
 * @author Daren Stotler
 * @see RootSolverException
 */

/*
 * $Log: Solved.java,v $
 * Revision 1.1.1.1  1999/11/15 20:37:49  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 2.0 01-21-98 The end result is simpler than elegant...
 * 1.1 12-09-97 Try a more elegant approach.
 * 1.0 02-12-97 Finally give it a number.
 */
//interface Solved {

  /**
   * This is the function to be solved.
   * @param x point at which function is to be evaluated
   * @return function value for use in solution algorithm
   */
/*
 * public :
	double calcfOfX(double x);
}

*/



/*
 * class Bisection
 *
 *    Copyright (C) 1996-1999, Daren Stotler
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

//package rootsolvers;

/**
 * This class is intended to contain a variety of root-solving algorithms,
 * each with possibly distinct interfaces. The function to be solved is
 * made available through the Solved interface with its calcf)OfX method.
 * Hence, each algorithm method will take as a first argument a Solved object.
 * Done in this manner, these algorithm methods can all be static.
 * It is also sensible to have the algorithm methods return the root as a
 * double. The rest of the arguments may vary with the algorithm. Use of
 * this class and the Solved interface is demonstrated in the SolversTest
 * application. This approach to using an interface closely follows the
 * examples in Core Java 1.1, Volume 1 by Horstmann & Cornell.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 1999/11/15 20:37:49 $.
 * @author Daren Stotler
 * @see Solvers
 * @see Solved
 * @see RootSolverException
 * @see SolversTest
 */

/*
 * $Log: Solvers.java,v $
 * Revision 1.1.1.1  1999/11/15 20:37:49  dstotler
 * Import SSFD into CVS
 *
 *
 * VERSION HISTORY PRIOR TO CVS:
 *
 * 2.0 01-21-98 Overhaul approach in favor of the simpler one from Horstmann.
 * 1.0 02-13-97 Finally give it a number.
 *
 */
class Solvers {

  /**
   * If one can bracket the root, the bisection algorithm can be used and
   * will find one root with virtual certainty. For more information, see
   * W. H. Press, B. P. Flannery, S. A. Teukolsky and W. T. Vetterling,
   * Numerical Recipes (Cambridge Univ., New York, 1988).
   * @param s Solved object containing the function to be solved
   * @param x1 one bound on the range of the root
   * @param x2 other bound
   * @exception RootSolverException thrown when a root isn't found
   * @return root of the function
   */
public :
	double bisection(SteadyStateFusionReactor s, double x1, double x2)/* throws RootSolverException*/ {

	//std::cout << "bisection x1: " << x1 << std::endl;
	//std::cout << "bisection x2: " << x2 << std::endl;

	double xacc = 1.e-3;
    int jmax = 40;

    double rtbis, dx, xmid;

    double fmid = s.calcfOfX(x2);
    //std::cout << "bisection fmid " <<  fmid << std::endl;
    double f = s.calcfOfX(x1);
    //std::cout << "bisection f " << f  << std::endl;

    //std::cout << "bisection test " << f * fmid << std::endl;

    if (f * fmid > 0){
    	//std::cout << "Interval does not bracket root" << std::endl;
    	return 0;
      throw /*new RootSolverException(*/"Interval does not bracket root"/*)*/;

    }
    //std::cout << "bisection check done " << f * fmid << std::endl;


    if (f < 0.) {
      rtbis = x1;
      dx = x2 - x1;
    }
    else {
      rtbis = x2;
      dx = x1 - x2;
    }

    for (int j=0; j<jmax; j++) {
      dx = 0.5 * dx;
      xmid = rtbis + dx;
      fmid = s.calcfOfX(xmid);
      if (fmid <= 0.) rtbis = xmid;
      if (fabs(dx) < xacc || fmid == 0.) return xmid;
    }
    throw /*new RootSolverException(*/"Convergence criteria unsatisfied"/*)*/;
  }
};


int calcFitness(double dMagneticField, double dPlasmaDensity, double dPower){

    ExpTauE iter89P_ = ExpTauE(0.0381, 0.5, 0.5, 0.85, 0.1, 0.2, 0.3, 1.2, -0.5);

    /*
     * For simplicity, the size of the reactor and its magnetic safety
     * factor q, are fixed to those of BPX.
     */
    double abpx = 0.795;
    double rbpx = 2.59;
    double qbpx = 2.3;

    /*
     * Allocate and initialize Observables.
     * related variables.
     */
    ObservableDbl oBField_ = ObservableDbl(dMagneticField);
    ObservableDbl oDensity_ = ObservableDbl(dPlasmaDensity);
    ObservableDbl oPaux_ = ObservableDbl(dPower);
    ObservableDbl oTemperature_ = ObservableDbl(0.);
    ObservableDbl oScore_ = ObservableDbl(0.);


    /*
     * Attempt to initialize FusionReactor bpx_.
     */
    FusionReactor bpx_ = FusionReactor(abpx, rbpx, qbpx, oBField_, oDensity_, oPaux_, oTemperature_, oScore_, iter89P_);

    SteadyStateFusionReactor steadybpx_ = SteadyStateFusionReactor(&bpx_, oTemperature_);


    Solvers solvers;
    solvers.bisection(steadybpx_,10.,500.);  // Bracket temperature root - in 1.e6 Kelvin!

    int score = bpx_.calcOScore();
	return score;
}

void StringExplode(std::string str, std::string separator, std::vector<std::string>* results){
    std::size_t found;
    found = str.find_first_of(separator);
    while(found != std::string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}

void CalcAll(){
	double dMaxScore = 0;
	double dPower;
	double dMagnetic;
	double dPlasma;

	double dStep = 0.01;

	for(double i = 0; i <= 1; i += dStep){
		std::cout << i << "%" << std::endl;

		for(double j = 0; j <= 14; j += dStep){
			for(double k = 0.01; k <= 6; k += dStep){
				double dScore = calcFitness(j, k, i );
				if(dScore > dMaxScore){
					dPower = i;
					dMagnetic = j;
					dPlasma = k;
					dMaxScore = dScore;
				}

			}
		}
	}

	std::cout << "Max score: " << dMaxScore << std::endl;
	std::cout << "Power: " << dPower << std::endl;
	std::cout << "Magnetic: " << dMagnetic << std::endl;
	std::cout << "Plasma: " << dPlasma << std::endl;
}

int main(int argc, char *argv[]) {

	std::string strFileName = "";

	int nMode = 0;

	//CalcAll();

	//std::cout << calcFitness(7.0, 3.0, 40);

	bool bVerbose = false;
	if(argc == 4){
		strFileName= argv[1];
		 if(argv[2] == std::string("-highest")){
			 nMode = 1;
		 }
		 else if (argv[2] == std::string("-average")){
			 nMode = 2;
		 }
		bVerbose = true;
	}
	else if(argc == 3){
		strFileName= argv[1];
		 if(argv[2] == std::string("-highest")){
			 nMode = 1;
		 }
		 else if (argv[2] == std::string("-average")){
			 nMode = 2;
		 }
	}
	else{
		std::cout << "Usage: Tokamak.exe inputFilename [-highest , -average] [-verbose]" << std::endl;
		exit(1);
	}

	std::vector<int> vnScores;

    // ifstream is used for reading files
    // We'll read from a file called Sample.dat
    ifstream inf(strFileName.c_str());

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        cerr << strFileName << " could not be opened for reading!" << endl;
        exit(2);
    }

    // While there's still stuff left to read
    while (inf)
    {
        // read stuff from the file into a string and print it
        std::string strInput;
        getline(inf, strInput);
        std::vector<std::string> vstrData;
        if(strInput != ""){
        	StringExplode(strInput, " ", &vstrData);
        	if(vstrData[2] == "0"){
        		vstrData[2] = "0.01";
        	}

        	double dScore;
        	dScore = calcFitness(atof(vstrData[1].c_str()), atof(vstrData[2].c_str()), atof(vstrData[0].c_str()) );

        	vnScores.push_back(dScore);

        	if(bVerbose){
        	        	std::cout << "\nMagnetic Field: \t" << atof(vstrData[1].c_str())
        	        			<< "\nPlasma Density: \t" << atof(vstrData[2].c_str())
        	        			<< "\nAuxiliary Power: \t" << atof(vstrData[0].c_str())
        	        			<< "\nSCORE: \t" << dScore << std::endl ;

        	}
        }
    }


    int nScore = 0;
    switch (nMode)
    {
        case 1:
        	nScore = *max_element(vnScores.begin(), vnScores.end()) ;
            break;
        case 2:
        	double average;
        	average = std::accumulate(vnScores.begin(), vnScores.end(), 0)/vnScores.size();
        	nScore = (int) average;
            break;

        default:
            std::cout << "Unknown mode";
            exit(3);
            break;
    }

    if(bVerbose){
    	std::cout << "\n TOTAL SCORE: " << nScore << std::endl;
    }


	return nScore;
}

