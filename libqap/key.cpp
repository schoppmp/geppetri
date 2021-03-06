/**
 *
 * Copyright (c) 2016-2017 Koninklijke Philips N.V. All rights reserved. A
 * copyright license for redistribution and use in source and binary forms,
 * with or without modification, is hereby granted for non-commercial,
 * experimental and research purposes, provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimers.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimers in the
 *   documentation and/or other materials provided with the distribution. If
 *   you wish to use this software commercially, kindly contact
 *   info.licensing@philips.com to obtain a commercial license.
 *
 * This license extends only to copyright and does not include or grant any
 * patent license or other license whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <gmpxx.h>
#define BN_SUPPORT_SNARK
#define MIE_ATE_USE_GMP
#include <bn.h>

using namespace bn;

#include <ostream>
#include "key.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const masterkey& x) {
    os << "geppetri_masterkey [ " << x.g_s.size() << " " << x.g_als.size() << endl;

    os << " ";
    for (unsigned int j = 0; j < x.g_als.size(); j++) os << " " << x.g_als[j];
    os << endl;

    for (unsigned int i = 0; i < x.g_s.size(); i++) {
        os << "  " << x.g_s[i] << " " << x.g2_s[i] << " " << x.g_rcs[i];
        for (unsigned int j = 0; j < x.g_als.size(); j++) os << " " << x.g_rcalcs[j][i];
        os << endl;
    }

    os << "]";

    return os;
}

std::istream& operator>>(std::istream& is, masterkey& x) {
    string checktok; is >> checktok;
    if (checktok != "geppetri_masterkey") throw std::ios_base::failure((string("Expected \"geppetri_masterkey\", got \"") + checktok + "\"").c_str());

    char br; is >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad masterkey: expected \"[\", got \"") + br + "\"").c_str());

    unsigned int nroots, ninp;

    is >> nroots;
    is >> ninp;

    x.g_als = vector<Ec2>(ninp);
    for (unsigned int j = 0; j < ninp; j++) is >> x.g_als[j];

    x.g_s = vector<Ec1>(nroots);
    x.g2_s = vector<Ec2>(nroots);
    x.g_rcs = vector<Ec1>(nroots);
    x.g_rcalcs = vector<vector<Ec2>>(ninp);
    for (unsigned int j = 0; j < ninp; j++) x.g_rcalcs[j] = vector<Ec2>(nroots);

    for (unsigned int i = 0; i < nroots; i++) {
        is >> x.g_s[i];
        is >> x.g2_s[i];
        is >> x.g_rcs[i];
        for (unsigned int j = 0; j < ninp; j++) is >> x.g_rcalcs[j][i];
    }

    is >> br;
    if (br != ']') throw std::ios_base::failure((string("Bad masterkey: expected \"]\", got \"") + br + "\"").c_str());
    return is;

}


ostream& operator<<(ostream& os, const wirevk& vk) {
    os << "[ " << vk.g_rvvk << " " << vk.g_rwwk << " " << vk.g_ryyk << " ]";
    return os;
}

std::istream& operator>>(std::istream& in, wirevk& vk) {
    char br; in >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad wirevk: expected \"[\", got \"") + br + "\"").c_str());

    in >> vk.g_rvvk;
    in >> vk.g_rwwk;
    in >> vk.g_ryyk;

    in >> br;
    if (br != ']') throw std::ios_base::failure((string("Bad wirevk: expected \"]\", got \"") + br + "\"").c_str());
    return in;
}

std::ostream& operator<<(std::ostream& os, const wireek& ek) {
    os << "[ " << ((wirevk) ek) << " " << ek.g_rvavvk << " " << ek.g_rwawwk << " " << ek.g_ryayyk << " " << ek.g_rvvkrwwkryyk << " ]";
    return os;
}

std::istream& operator>>(std::istream& in, wireek& ek) {
    char br; in >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad wireek: expected \"[\", got \"") + br + "\"").c_str());

    in >> ((wirevk&) ek);
    in >> ek.g_rvavvk >> ek.g_rwawwk >> ek.g_ryayyk >> ek.g_rvvkrwwkryyk;

    in >> br;
    if (br != ']') throw std::ios_base::failure((string("Bad wireek: expected \"]\", got \"") + br + "\"").c_str());
    return in;
}

ostream& operator<<(ostream& os, const blockvk& vk) {
    os << "[ " << vk.g2al << " " << vk.g2beta << " ]";
    return os;
}

std::istream& operator>>(std::istream& in, blockvk& x) {
    char br; in >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad blockvk: expected \"[\", got \"") + br + "\"").c_str());

    in >> x.g2al >> x.g2beta;

    in >> br;
    if (br != ']') throw std::ios_base::failure((string("Bad blockvk: expected \"]\", got \"") + br + "\"").c_str());
    return in;
}





std::ostream& operator<<(std::ostream& os, const blockek& x) {
    os << "[ " << x.g2als.size() << "  " << x.g2al << " " << x.g1betar1 << " " << x.g1betar2;
    for (unsigned int i=0; i < x.g2als.size(); i++)
        os << "    " << x.g2als[i] << " " << x.g1betas[i] << endl;
    os << "  " << x.gstart << endl;
    os << "  ]" << endl;
    return os;
}


std::istream& operator>>(std::istream& in, blockek& x) {
    char br; in >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad blockek: expected \"[\", got \"") + br + "\"").c_str());

    unsigned int sz;
    in >> sz;

    in >> x.g2al >> x.g1betar1 >> x.g1betar2;

    x.g2als = vector<Ec2>(sz);
    x.g1betas = vector<Ec1>(sz);

    for (unsigned int i = 0; i < sz; i++)
        in >> x.g2als[i] >> x.g1betas[i];

    in >> x.gstart;

    in >> br;
    if (br != ']') throw std::ios_base::failure((string("Bad blockek: expected \"]\", got \"") + br + "\"").c_str());

    return in;
}

std::ostream& operator<<(std::ostream& os, const qapvk& x) {
    os << "geppetri_qapvk [" << endl <<
          "  " << x.g2alv << endl <<
          "  " << x.g1alw << endl <<
          "  " << x.g2aly << endl <<
          "  " << x.g2ryt << endl <<
          "  " << x.g1bet << endl <<
          "  " << x.g2bet << endl;
    for (auto const& it: x.blocks) {
        os << "  " << it.first << " " << it.second << endl;
    }
    os << "]" << endl;
    return os;
}


std::istream& operator>>(std::istream& in, qapvk& x) {
    string checktok; in >> checktok;
    if (checktok != "geppetri_qapvk") throw std::ios_base::failure((string("Expected \"geppetri_qapvk\", got \"") + checktok + "\"").c_str());

    char br; in >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad qapvk: expected \"[\", got \"") + br + "\"").c_str());

    in >> x.g2alv >> x.g1alw >> x.g2aly >> x.g2ryt >> x.g1bet >> x.g2bet;

    string tok;
    while (!(in>>tok).eof() && tok!="" && tok!="]")
        in >> x.blocks[tok];

    if (tok != "]") throw std::ios_base::failure((string("Bad qapvk: expected \"]\", got \"") + br + "\"").c_str());

    return in;
}

std::ostream& operator<<(std::ostream& os, const qapek& x) {
    os << "geppetri_qapek [" << endl;

    os << "  " << x.g_rvt << endl;
    os << "  " << x.g_ryt << endl;
    os << "  " << x.g_rvavt << endl;
    os << "  " << x.g_rwawt << endl;
    os << "  " << x.g_ryayt << endl;
    os << "  " << x.g2_rwt << endl;
    os << "  " << x.g_beta << endl;
    os << "  " << x.g_rvbt << endl;
    os << "  " << x.g_rwbt << endl;
    os << "  " << x.g_rybt << endl;

    for (auto const& it: x.blocks) {
        os << "  " << it.first << " " << it.second;
    }

    os << "  ." << endl;

    for (auto const& it: x.wires) {
        os << "  " << it.first << " " << it.second << endl;
    }

    os << "]" << endl;

    return os;
}

std::istream& operator>>(std::istream& is, qapek& x) {
    string checktok; is >> checktok;
    if (checktok != "geppetri_qapek") throw std::ios_base::failure((string("Expected \"geppetri_qapek\", got \"") + checktok + "\"").c_str());

    char br; is >> br;
    if (br != '[') throw std::ios_base::failure((string("Bad qapek: expected \"[\", got \"") + br + "\"").c_str());

    is >> x.g_rvt >> x.g_ryt >> x.g_rvavt >> x.g_rwawt >> x.g_ryayt >> x.g2_rwt >> x.g_beta >> x.g_rvbt >> x.g_rwbt >> x.g_rybt;

    string tok;

    while (!(is>>tok).eof() && tok != ".") {
        is >> x.blocks[tok];
    }

    while (!(is>>tok).eof() && tok != "]") {
        is >> x.wires[tok];
    }

    if (tok!="]")
        throw std::ios_base::failure((string("Bad qapek: expected \"block\" or \"wire\", got \"") + br + "\"").c_str());

    return is;
}
