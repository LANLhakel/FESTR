/**
 * @file Zone.cpp
 * @brief Spatial zone, defined by a list bounding Face objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 8 December 2014\n
 * Last modified on 6 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Zone.h>

#include <FaceFactory.h>
#include <Table.h>
#include <utils.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>

#ifdef MPI
#include <mpi.h>
#endif

//-----------------------------------------------------------------------------

Zone::Zone():
    my_id(0), face(), te(-1.0), tr(-1.0),
    np(-1.0), nmat(0), mat(), fp(), ne(0.0), emis(), absp(), scat() {}

//-----------------------------------------------------------------------------

Zone::Zone(const size_t my_id_in): my_id(my_id_in), face(),
    te(-1.0), tr(-1.0),
    np(-1.0), nmat(0), mat(), fp(), ne(0.0), emis(), absp(), scat() {}

//-----------------------------------------------------------------------------

Zone::Zone(std::ifstream &geometry, std::ifstream &material):
    my_id(0), face(), te(-1.0), tr(-1.0),
    np(-1.0), nmat(0), mat(), fp(), ne(0.0), emis(), absp(), scat()
{
    load_geo(geometry);
    load_mat(material);
}

//-----------------------------------------------------------------------------

void Zone::clear()
{
    my_id = 0;
    face.clear();
    te = -1.0;
    tr = -1.0;
    np = -1.0;
    nmat = 0;
    mat.clear();
    fp.clear();
    ne = 0.0;
    emis.clear();
    absp.clear();
    scat.clear();
}

//-----------------------------------------------------------------------------

void Zone::set_id(const size_t my_id_in)
{
    my_id = my_id_in;
}

//-----------------------------------------------------------------------------

size_t Zone::get_id() const
{
    return my_id;
}

//-----------------------------------------------------------------------------

void Zone::add_face(FacePtr f)
{
    face.emplace_back(std::move(f));
}

//-----------------------------------------------------------------------------

FacePtr Zone::get_face(const short int i) const
{
    return face.at(static_cast<size_t>(i));
}

//-----------------------------------------------------------------------------

void Zone::set_ne(const double ne_in)
{
    ne = ne_in;
}

//-----------------------------------------------------------------------------

double Zone::get_ne() const
{
    return ne;
}

//-----------------------------------------------------------------------------

void Zone::set_te(const double te_in)
{
    te = te_in;
}

//-----------------------------------------------------------------------------

double Zone::get_te() const
{
    return te;
}

//-----------------------------------------------------------------------------

void Zone::set_tr(const double tr_in)
{
    tr = tr_in;
}

//-----------------------------------------------------------------------------

double Zone::get_tr() const
{
    return tr;
}

//-----------------------------------------------------------------------------

void Zone::set_np(const double np_in)
{
    np = np_in;
}

//-----------------------------------------------------------------------------

double Zone::get_np() const
{
    return np;
}

//-----------------------------------------------------------------------------

void Zone::set_nmat(const unsigned short int nmat_in)
{
    nmat = nmat_in;
}

//-----------------------------------------------------------------------------

unsigned short int Zone::get_nmat() const
{
    return nmat;
}

//-----------------------------------------------------------------------------

void Zone::set_mat(const std::vector<std::string> &mat_in)
{
    mat = mat_in;
}

//-----------------------------------------------------------------------------

std::string Zone::mat_at(const unsigned short int i) const
{
    return mat.at(i);
}

//-----------------------------------------------------------------------------

const std::vector<std::string> & Zone::get_mat() const
{
    return mat;
}

//-----------------------------------------------------------------------------

void Zone::set_fp(const std::vector<double> &fp_in)
{
    fp = fp_in;
}

//-----------------------------------------------------------------------------

double Zone::fp_at(const unsigned short int i) const
{
    return fp.at(i);
}

//-----------------------------------------------------------------------------

const std::vector<double> & Zone::get_fp() const
{
    return fp;
}

//-----------------------------------------------------------------------------

size_t Zone::size() const
{
    return face.size();
}

//-----------------------------------------------------------------------------

Vector3d Zone::zone_point(const Grid &g, const Vector3d &p) const
{
    Vector3d s;
    std::for_each(face.begin(), face.end(),
                  [&](const FacePtr f){s += f->face_point(g, p);});
    return s / size();
}

//-----------------------------------------------------------------------------

RetIntercept Zone::hit(const Grid &g, const Vector3d &p, const Vector3d &u,
                       const FaceID &fid) const
{
    // minimum_Zone_size cannot be smaller than ~ Bohr radius (5e-9 cm);
    // choosing minimum_Zone_size = 1e-8 cm, then:
    // photon_time_of_flight = minimum_Zone_size / speed_of_light
    //                       = (1e-8 cm) / (3e10 cm/s) ~ 3e-19 s >~ EQT = 1e-19
    const double EQT = 1.0e-19;
    RetIntercept rv, pt;
    const size_t n = size();

    rv.t = Vector3d::get_big();
    for (size_t i = 0; i < n; ++i) // loop over *this Zone's Faces
    {
        pt = face.at(i)->intercept(g, p, u, EQT, fid);
        if (pt.is_found  &&  pt.t < rv.t) rv = pt;
    }

    if (!rv.is_found)
    {   // try again, this time tracing from zp instead of p
        Vector3d zp = zone_point(g, p);
        rv.t = Vector3d::get_big();
        for (size_t i = 0; i < n; ++i) // loop over *this Zone's Faces
        {
            pt = face.at(i)->intercept(g, zp, u, EQT, fid);
            if (pt.is_found  &&  pt.t < rv.t) rv = pt;
        }
    }

    return rv;
}

//-----------------------------------------------------------------------------

std::string Zone::to_string() const
{
    const size_t n = size();
    std::string s("Zone");
    s += utils::int_to_string(my_id, ' ', cnst::INT_WIDTH) + "\n";
    s += utils::int_to_string(n, ' ', cnst::INT_WIDTH) + "\n";
    for (size_t i = 0; i < n; ++i)
    {
        s += face.at(i)->to_string();
        if (i < n-1) s += "\n";
    }
    return s;
}

//-----------------------------------------------------------------------------

void Zone::load_geo(std::ifstream &geometry)
{
    clear();
    size_t nfaces;
    geometry >> my_id >> nfaces;
    #include <load_Faces.inc>
}

//-----------------------------------------------------------------------------

void Zone::load_mat(std::ifstream &material)
{
    size_t j;
    material >> j; // my_id already read in by load_geo()
    utils::find_word(material, "te");
    material >> te;
    utils::find_word(material, "tr");
    material >> tr;
    utils::find_word(material, "np");
    material >> np;
    utils::find_word(material, "nmat");
    material >> nmat;
    utils::find_word(material, "material");
    std::string str;
    getline(material, str); // skip over the rest of this line
    for (unsigned short int i = 0; i < nmat; ++i)
    {
        std::string s;
        double x;
        material >> s >> x;
        mat.emplace_back(std::move(s));
        fp.emplace_back(std::move(x));
    }
}

//-----------------------------------------------------------------------------

void Zone::load_spectra(const Database &d, const Table &tbl,
                        size_t &ite, size_t &itr, size_t &ine,
                        const std::string &symmetry, const size_t ix,
                        const bool analysis,
                        const size_t jmin, const size_t jmax,
                        ArrDbl &em, ArrDbl &ab, ArrDbl &sc) // not const
{
    size_t nhv_max = d.get_nhv();
    size_t nhv = jmax - jmin + 1;
    em.assign(nhv, 0.0);
    ab.assign(nhv, 0.0);
    sc.assign(nhv, 0.0);

    if (nmat > 0)
    {
        /* NOTE:
         In analysis mode with spherical symmetry we are "peeling the onion";
         in that case the ordering of Rays, as they are sent through the Mesh,
         is reversed from the original outward direction. Hence the storing of
         optical data is not used in that case, as it relies on shooting the
         central Ray through the Mesh first (since that Ray is guaranteed
         to cross all spherical Zones in the Mesh).
         */
        if ((symmetry == "none") || analysis ||
            ((symmetry != "none") && (ix == 0))) // ix == 0 == central Ray
        {
            ArrDbl v; // working array used by each material and quantity
            v.assign(nhv, 0.0); // actually allocate nhv elements

            NeData ne_data(d.find_ne(tbl,te,ite,tr,itr,np,nmat,mat,fp,ine));
            ne = ne_data.first;
            std::string froot, fname;
            double fpop;
            const std::string dirpath(d.get_path() + "spectra/");
            for (unsigned short int i = 0; i < nmat; ++i)
            {
                std::string m(tbl.get_F(mat.at(i)));
                froot = dirpath + m + "/" + m + ne_data.second;
                fpop = fp.at(i);

                fname = froot + "em.txt";
                utils::load_array(fname, nhv_max, jmin, jmax, v);
                em  +=  fpop * v;

                fname = froot + "ab.txt";
                utils::load_array(fname, nhv_max, jmin, jmax, v);
                ab  +=  fpop * v;

                fname = froot + "sc.txt";
                utils::load_array(fname, nhv_max, jmin, jmax, v);
                sc  +=  fpop * v;
            }
            em *= np;
            ab *= np;
            sc *= np;

            if (symmetry != "none") // in 1-D, save spectral data from ix == 0
            {   // Ray for reuse by other Rays within the same time interval
                emis = em;
                absp = ab;
                scat = sc;
            }
        }
        else // (symmetry != "none") && (ix > 0), &&!analysis, retrieve
             // saved data calculated earlier for the central Ray (ix == 0)
        {
            em = emis;
            ab = absp;
            sc = scat;
        }

    } // nmat > 0
}

//-----------------------------------------------------------------------------

std::string Zone::mat_to_string_full() const
{
    std::string s("Zone");
    s += utils::int_to_string(my_id, ' ', cnst::INT_WIDTH) + "\n";
    s += "ne" + utils::double_to_string(ne) + " electrons/cm3\n";
    s += "te" + utils::double_to_string(te) + " eV\n";
    s += "tr" + utils::double_to_string(tr) + " eV\n";
    s += "np" + utils::double_to_string(np) + " particles/cm3\n";
    s += "nmat" + utils::int_to_string(nmat, ' ', cnst::INT_WIDTH) + "\n";
    s += "material fraction";
    for (unsigned short int i = 0; i < nmat; ++i)
    {
        s += "\n" + mat.at(i) + utils::double_to_string(fp.at(i));
    }

    return s;
}

//-----------------------------------------------------------------------------

std::string Zone::mat_to_string_plot() const
{
    std::string s("");
    s += utils::double_to_string(ne) + utils::double_to_string(te)
       + utils::double_to_string(tr) + utils::double_to_string(np);
    for (unsigned short int i = 0; i < nmat; ++i)
        s += utils::double_to_string(fp.at(i));

    return s;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Zone &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

const size_t Zone::BOUNDING_ZONE = Face::BOUNDING_SPHERE.my_zone;

//-----------------------------------------------------------------------------

//  end Zone.cpp
