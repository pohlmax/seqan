// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2015, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: Hannes Hauswedell <hannes.hauswedell@fu-berlin.de>
// ==========================================================================
// Tests for the blast module
// ==========================================================================

#include <fstream>

using namespace seqan;

template <typename TArg,
          typename... TArgs>
inline void
clear(TArg & arg, TArgs & ... args)
{
    clear(arg);
    clear(args...);
}

static constexpr char const * out =
"# BLASTX 2.2.26+\n"
"# Query: SHAA003TF  Sample 1 Mate SHAA003TR trimmed_to 27 965\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# 0 hits found\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA003TR  Sample 1 Mate SHAA003TF trimmed_to 17 935\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# 0 hits found\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA004TF  Sample 1 Mate SHAA004TR trimmed_to 25 828\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: query id, subject id, % identity, alignment length, mismatches, gap opens, q. start, q. end, s. start, s. end, evalue, bit score\n"
"# 17 hits found\n"
"SHAA004TF\tsp|P0A916|OMPW_SHIFL\t50.43\t115\t49\t2\t389\t733\t1\t107\t1e-26\t108\n"
"SHAA004TF\tsp|P0A915|OMPW_ECOLI\t50.43\t115\t49\t2\t389\t733\t1\t107\t1e-26\t108\n"
"SHAA004TF\tsp|P17266|OMPW_VIBCH\t52.21\t113\t45\t2\t410\t733\t4\t112\t5e-26\t106\n"
"SHAA004TF\tsp|Q8ZP50|OMPW_SALTY\t50.43\t115\t49\t2\t389\t733\t1\t107\t3e-24\t101\n"
"SHAA004TF\tsp|Q8Z7E2|OMPW_SALTI\t50.43\t115\t49\t2\t389\t733\t1\t107\t3e-24\t101\n"
"SHAA004TF\tsp|P19766|INSB_SHISO\t100.00\t18\t0\t0\t803\t750\t114\t131\t4e-04\t43.1\n"
"SHAA004TF\tsp|P19765|INSB_SHIFL\t100.00\t18\t0\t0\t803\t750\t114\t131\t4e-04\t43.1\n"
"SHAA004TF\tsp|P03831|INBD_SHIDY\t100.00\t18\t0\t0\t803\t750\t114\t131\t4e-04\t43.1\n"
"SHAA004TF\tsp|P59843|INSB_HAEDU\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF31|INSB_ECOLX\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF30|INSB8_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF29|INSB6_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF28|INSB5_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P57998|INSB4_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF25|INSB1_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF27|INSB3_ECOLI\t94.44\t18\t1\t0\t803\t750\t150\t167\t0.004\t40.8\n"
"SHAA004TF\tsp|P0CF26|INSB2_ECOLI\t94.44\t18\t1\t0\t803\t750\t150\t167\t0.004\t40.8\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA004TR  Sample 1 Mate SHAA004TF trimmed_to 20 853\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: query id, subject id, % identity, alignment length, mismatches, gap opens, q. start, q. end, s. start, s. end, evalue, bit score\n"
"# 2 hits found\n"
"SHAA004TR\tsp|Q0HTA5|META_SHESR\t100.00\t77\t0\t0\t232\t2\t1\t77\t3e-42\t152\n"
"SHAA004TR\tsp|Q0HGZ8|META_SHESM\t100.00\t77\t0\t0\t232\t2\t1\t77\t3e-42\t152\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA005TR  Sample 1 Mate SHAA005TF trimmed_to 22 960\n"
"# Datacase: /tmp/uniprot_sprot.fasta\n"
"# 0 hits found\n";
// I introduced an artificial typo in the last "Database" to test for strictness
// implementations

static constexpr char const * legacyout =
"# BLASTX 2.2.26 [Sep-21-2011]\n"
"# Query: SHAA003TF  Sample 1 Mate SHAA003TR trimmed_to 27 965\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: Query id, Subject id, % identity, alignment length, mismatches, gap openings, q. start, q. end, s. start, s. end, e-value, bit score\n"
"# BLASTX 2.2.26 [Sep-21-2011]\n"
"# Query: SHAA003TR  Sample 1 Mate SHAA003TF trimmed_to 17 935\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: Query id, Subject id, % identity, alignment length, mismatches, gap openings, q. start, q. end, s. start, s. end, e-value, bit score\n"
"# BLASTX 2.2.26 [Sep-21-2011]\n"
"# Query: SHAA004TF  Sample 1 Mate SHAA004TR trimmed_to 25 828\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: Query id, Subject id, % identity, alignment length, mismatches, gap openings, q. start, q. end, s. start, s. end, e-value, bit score\n"
"SHAA004TF\tsp|P0A916|OMPW_SHIFL\t50.43\t115\t57\t2\t389\t733\t1\t107\t1e-26\t108\n"
"SHAA004TF\tsp|P0A915|OMPW_ECOLI\t50.43\t115\t57\t2\t389\t733\t1\t107\t1e-26\t108\n"
"SHAA004TF\tsp|P17266|OMPW_VIBCH\t52.21\t113\t49\t2\t410\t733\t4\t112\t5e-26\t106\n"
"SHAA004TF\tsp|Q8ZP50|OMPW_SALTY\t50.43\t115\t57\t2\t389\t733\t1\t107\t3e-24\t101\n"
"SHAA004TF\tsp|Q8Z7E2|OMPW_SALTI\t50.43\t115\t57\t2\t389\t733\t1\t107\t3e-24\t101\n"
"SHAA004TF\tsp|P19766|INSB_SHISO\t100.00\t18\t0\t0\t803\t750\t114\t131\t4e-04\t43.1\n"
"SHAA004TF\tsp|P19765|INSB_SHIFL\t100.00\t18\t0\t0\t803\t750\t114\t131\t4e-04\t43.1\n"
"SHAA004TF\tsp|P03831|INBD_SHIDY\t100.00\t18\t0\t0\t803\t750\t114\t131\t4e-04\t43.1\n"
"SHAA004TF\tsp|P59843|INSB_HAEDU\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF31|INSB_ECOLX\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF30|INSB8_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF29|INSB6_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF28|INSB5_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P57998|INSB4_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF25|INSB1_ECOLI\t100.00\t18\t0\t0\t803\t750\t150\t167\t6e-04\t43.1\n"
"SHAA004TF\tsp|P0CF27|INSB3_ECOLI\t94.44\t18\t1\t0\t803\t750\t150\t167\t0.004\t40.8\n"
"SHAA004TF\tsp|P0CF26|INSB2_ECOLI\t94.44\t18\t1\t0\t803\t750\t150\t167\t0.004\t40.8\n"
"# BLASTX 2.2.26 [Sep-21-2011]\n"
"# Query: SHAA004TR\tSample 1 Mate SHAA004TF trimmed_to 20 853\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: Query id, Subject id, % identity, alignment length, mismatches, gap openings, q. start, q. end, s. start, s. end, e-value, bit score\n"
"SHAA004TR\tsp|Q0HTA5|META_SHESR\t100.00\t77\t0\t0\t232\t2\t1\t77\t3e-42\t152\n"
"SHAA004TR\tsp|Q0HGZ8|META_SHESM\t100.00\t77\t0\t0\t232\t2\t1\t77\t3e-42\t152\n"
"# BLASTX 2.2.26 [Sep-21-2011]\n"
"# Query: SHAA005TR  Sample 1 Mate SHAA005TF trimmed_to 22 960\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: Query id, Subject id, % identity, alignment length, mismatches, gap openings, q. start, q. end, s. start, s. end, e-value, bit score\n";

static constexpr char const * out_custom1 =
"# BLASTX 2.2.26+\n"
"# Query: SHAA003TF  Sample 1 Mate SHAA003TR trimmed_to 27 965\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# 0 hits found\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA003TR  Sample 1 Mate SHAA003TF trimmed_to 17 935\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# 0 hits found\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA004TF  Sample 1 Mate SHAA004TR trimmed_to 25 828\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: query id, subject id, alignment length, identical, mismatches, positives, gaps, q. start, q. end, s. start, s. end, query/sbjct frames, bit score\n"
"# 17 hits found\n"
"SHAA004TF\tsp|P0A916|OMPW_SHIFL\t115\t58\t49\t72\t8\t389\t733\t1\t107\t2/0\t108\n"
"SHAA004TF\tsp|P0A915|OMPW_ECOLI\t115\t58\t49\t72\t8\t389\t733\t1\t107\t2/0\t108\n"
"SHAA004TF\tsp|P17266|OMPW_VIBCH\t113\t59\t45\t72\t9\t410\t733\t4\t112\t2/0\t106\n"
"SHAA004TF\tsp|Q8ZP50|OMPW_SALTY\t115\t58\t49\t69\t8\t389\t733\t1\t107\t2/0\t101\n"
"SHAA004TF\tsp|Q8Z7E2|OMPW_SALTI\t115\t58\t49\t69\t8\t389\t733\t1\t107\t2/0\t101\n"
"SHAA004TF\tsp|P19766|INSB_SHISO\t18\t18\t0\t18\t0\t803\t750\t114\t131\t-1/0\t43.1\n"
"SHAA004TF\tsp|P19765|INSB_SHIFL\t18\t18\t0\t18\t0\t803\t750\t114\t131\t-1/0\t43.1\n"
"SHAA004TF\tsp|P03831|INBD_SHIDY\t18\t18\t0\t18\t0\t803\t750\t114\t131\t-1/0\t43.1\n"
"SHAA004TF\tsp|P59843|INSB_HAEDU\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P0CF31|INSB_ECOLX\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P0CF30|INSB8_ECOLI\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P0CF29|INSB6_ECOLI\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P0CF28|INSB5_ECOLI\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P57998|INSB4_ECOLI\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P0CF25|INSB1_ECOLI\t18\t18\t0\t18\t0\t803\t750\t150\t167\t-1/0\t43.1\n"
"SHAA004TF\tsp|P0CF27|INSB3_ECOLI\t18\t17\t1\t17\t0\t803\t750\t150\t167\t-1/0\t40.8\n"
"SHAA004TF\tsp|P0CF26|INSB2_ECOLI\t18\t17\t1\t17\t0\t803\t750\t150\t167\t-1/0\t40.8\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA004TR  Sample 1 Mate SHAA004TF trimmed_to 20 853\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# Fields: query id, subject id, alignment length, identical, mismatches, positives, gaps, q. start, q. end, s. start, s. end, query/sbjct frames, bit score\n"
"# 2 hits found\n"
"SHAA004TR\tsp|Q0HTA5|META_SHESR\t77\t77\t0\t77\t0\t232\t2\t1\t77\t-2/0\t152\n"
"SHAA004TR\tsp|Q0HGZ8|META_SHESM\t77\t77\t0\t77\t0\t232\t2\t1\t77\t-2/0\t152\n"
"# BLASTX 2.2.26+\n"
"# Query: SHAA005TR  Sample 1 Mate SHAA005TF trimmed_to 22 960\n"
"# Database: /tmp/uniprot_sprot.fasta\n"
"# 0 hits found\n";


//legacy doesnt have interface with fieldList so we need to wrap around the call
template <typename TMatch,
          typename TIt,
          typename TFields,
          BlastFormatFile f,
          BlastFormatProgram p>
inline void
_readMatchWrap(TMatch & match, TIt & it, TFields const &, bool,
               BlastFormat<f, p, BlastFormatGeneration::BLAST_LEGACY> const &)
{
    typedef BlastFormat<f, p, BlastFormatGeneration::BLAST_LEGACY> TFormat;
    readMatch(match, it, TFormat());
}

template <typename TMatch,
          typename TIt,
          typename TFields,
          BlastFormatFile f,
          BlastFormatProgram p>
inline void
_readMatchWrap(TMatch & match, TIt & it, TFields const & fields, bool useFields,
               BlastFormat<f, p, BlastFormatGeneration::BLAST_PLUS> const &)
{
    typedef BlastFormat<f, p, BlastFormatGeneration::BLAST_PLUS> TFormat;
    if (useFields)
        readMatch(match, it, TFormat());
    else
        readMatch(match, it, fields, TFormat());
}

template <typename TFormat>
void _test_blast_read_tabular_match(char const * string,
                                    bool defaults,
                                    TFormat const &)
{
    // only used when defaults == false
    typedef BlastMatchField<BlastFormatGeneration::BLAST_PLUS> TField;
    std::array<typename TField::Enum, 12> customFields
    {
        {
            TField::Enum::Q_SEQ_ID,
            TField::Enum::S_SEQ_ID,
            TField::Enum::LENGTH,
            TField::Enum::N_IDENT,
            TField::Enum::MISMATCH,
            TField::Enum::POSITIVE,
            TField::Enum::GAPS,
            TField::Enum::Q_START,
            TField::Enum::Q_END,
            TField::Enum::S_START,
            TField::Enum::S_END,
            TField::Enum::FRAMES,
            // actually BITSCORE is also in the file, but we are checking
            // that the implementation copes with less requested fields
            // than available ones which we defined as legal.
        }
    };



    const char * tempFilename = SEQAN_TEMP_FILENAME();
    char filenameBuffer[1000];
    strcpy(filenameBuffer, tempFilename);

    std::fstream fstream(filenameBuffer, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    SEQAN_ASSERT(fstream.is_open());

    fstream << string;
    fstream.seekg(0, std::ios::beg); // go back to beginning
    fstream.seekp(0, std::ios::beg); // go back to beginning
    auto it = directionIterator(fstream, Input());

//     Iterator<std::fstream, Rooted>::Type it = begin(fstream);
//     auto it = directionIterator(fstream, Bidirectional());
//     FormattedFile<> it(fstream);

    // first line is header
    SEQAN_ASSERT(!onMatch(it, TFormat()));

    // skip headers and comment lines
    skipUntilMatch(it, TFormat());

    //---- FIRST MATCH ---- //

    // now we should be onMatch
    SEQAN_ASSERT(onMatch(it, TFormat()));

    BlastMatch<> m;
    _readMatchWrap(m, it, customFields, defaults, TFormat());

    SEQAN_ASSERT_EQ(m.qId,          "SHAA004TF");
    SEQAN_ASSERT_EQ(m.sId,          "sp|P0A916|OMPW_SHIFL");
    SEQAN_ASSERT_EQ(m.identities,   58u /*(115u * 50.43) / 100*/);
    SEQAN_ASSERT_EQ(m.aliLength,    115u);
    if (string == legacyout) // legacy blast includes gaps in mismatches
        SEQAN_ASSERT_EQ(m.mismatches,   57u);
    else
        SEQAN_ASSERT_EQ(m.mismatches,   49u);
    SEQAN_ASSERT_EQ(m.qStart,       389u);
    SEQAN_ASSERT_EQ(m.qEnd,         733u);
    SEQAN_ASSERT_EQ(m.sStart,       1u);
    SEQAN_ASSERT_EQ(m.sEnd,         107u);

    if (defaults)
    {
        SEQAN_ASSERT_EQ(m.gapOpenings,  2u);
        SEQAN_ASSERT_LEQ(std::abs(m.bitScore - 108), 1e-3);
        SEQAN_ASSERT_LEQ(std::abs(m.eValue  - 1e-26), 1e-10);
    } else
    {
        SEQAN_ASSERT_EQ(m.positives,    72u);
        SEQAN_ASSERT_EQ(m.qFrameShift,  2);
        SEQAN_ASSERT_EQ(m.sFrameShift,  0);
    }
    // legacy blast includes gaps in mismatches, so gaps are only computed
    // for BLAST_PLUS
    if (getGenerationType(TFormat()) == BlastFormatGeneration::BLAST_PLUS)
    {
        if (string == legacyout) // legacy output with plus reader
            SEQAN_ASSERT_EQ(m.gaps,     0u /*(115u - 58 - 49)*/);
        else // plus output and plus reader
            SEQAN_ASSERT_EQ(m.gaps,     8u /*(115u - 58 - 49)*/);
    } else
    {
        SEQAN_ASSERT_EQ(m.gaps, std::numeric_limits<decltype(m.gaps)>::max());
    }
    //---- FIRST MATCH END ---- //

    // now we should be onMatch
    SEQAN_ASSERT(onMatch(it, TFormat()));

    unsigned count = 0;
    while (onMatch(it, TFormat()))
    {
        if (defaults) // skipMatch with verification
            skipMatch(it, true, TFormat());
        else
            skipMatch(it, false, TFormat());

        ++count;
    }

    // 16 further matches where skipped
    SEQAN_ASSERT_EQ(count, 16u);

    // back on header
    SEQAN_ASSERT(!onMatch(it, TFormat()));

    skipUntilMatch(it, TFormat());

    // skipMatch without verification
    skipMatch(it, TFormat());

    //---- LAST MATCH ---- //
    // read another match
    _readMatchWrap(m, it, customFields, defaults, TFormat());

    SEQAN_ASSERT_EQ(m.qId,          "SHAA004TR");
    SEQAN_ASSERT_EQ(m.sId,          "sp|Q0HGZ8|META_SHESM");
    SEQAN_ASSERT_EQ(m.identities,   77u /* (77u * 100) / 100 */);
    SEQAN_ASSERT_EQ(m.aliLength,    77u);
    SEQAN_ASSERT_EQ(m.mismatches,   0u);
    SEQAN_ASSERT_EQ(m.qStart,       232u);
    SEQAN_ASSERT_EQ(m.qEnd,         2u);
    SEQAN_ASSERT_EQ(m.sStart,       1u);
    SEQAN_ASSERT_EQ(m.sEnd,         77u);

    // legacy blast includes gaps in mismatches, so gaps are only computed
    // for BLAST_PLUS
    if (getGenerationType(TFormat()) == BlastFormatGeneration::BLAST_PLUS)
        SEQAN_ASSERT_EQ(m.gaps,     0u); // always zero here
    else
        SEQAN_ASSERT_EQ(m.gaps, std::numeric_limits<decltype(m.gaps)>::max());

    if (defaults)
    {
        SEQAN_ASSERT_EQ(m.gapOpenings,  0u);
        SEQAN_ASSERT_LEQ(std::abs(m.eValue  - 3e-42), 1e-10);
        SEQAN_ASSERT_LEQ(std::abs(m.bitScore - 152), 1e-3);
    } else
    {
        SEQAN_ASSERT_EQ(m.positives,    77u);
        SEQAN_ASSERT_EQ(m.qFrameShift, -2);
        SEQAN_ASSERT_EQ(m.sFrameShift,  0);
    }
    //---- LAST MATCH END ---- //

    // check if exceptions are properly thrown
    CharString exceptComment;
    SEQAN_TRY
    {
        readMatch(m, it, TFormat());
    } SEQAN_CATCH (ParseError const & e)
    {
        exceptComment = e.what();
    }

    SEQAN_ASSERT_EQ(exceptComment, "Not on beginning of Match (you should have "
                                   "skipped comments).");

    exceptComment = "";
    SEQAN_TRY
    {
        skipUntilMatch(it, TFormat());
    } SEQAN_CATCH (ParseError const & e)
    {
        exceptComment = e.what();
    }

    SEQAN_ASSERT_EQ(exceptComment, "EOF reached without finding Match.");

    fstream.close();
}

SEQAN_DEFINE_TEST(test_blast_read_tabular_match)
{
    // this tests BlastMatch#readMatch(), BlastMatch#skipMatch() and
    // BlastFormat#skipUntilMatch
    typedef BlastFormat<BlastFormatFile::TABULAR,
                        BlastFormatProgram::BLASTX,
                        BlastFormatGeneration::BLAST_PLUS> TFormat;
    _test_blast_read_tabular_match(out, true, TFormat());
    // basic match reading should work between plus and legacy
    _test_blast_read_tabular_match(legacyout, true, TFormat());
}

SEQAN_DEFINE_TEST(test_blast_read_tabular_match_legacy)
{
    // this tests BlastMatch#readMatch(), BlastMatch#skipMatch() and
    // BlastFormat#skipUntilMatch
    // with default columns (legacy format)
    typedef BlastFormat<BlastFormatFile::TABULAR,
                        BlastFormatProgram::BLASTX,
                        BlastFormatGeneration::BLAST_LEGACY> TFormat;
    _test_blast_read_tabular_match(legacyout, true, TFormat());
    // basic match reading should work between plus and legacy
    _test_blast_read_tabular_match(out, true, TFormat());
}

SEQAN_DEFINE_TEST(test_blast_read_tabular_match_customfields)
{
    // this tests BlastMatch#readMatch(), BlastMatch#skipMatch() and
    // BlastFormat#skipUntilMatch
    typedef BlastFormat<BlastFormatFile::TABULAR,
                        BlastFormatProgram::BLASTX,
                        BlastFormatGeneration::BLAST_PLUS> TFormat;
    _test_blast_read_tabular_match(out_custom1, false, TFormat());
    // custom columns not supported in legacy format
}



template <typename TFormat>
inline void
_test_blast_read_tabular_match_columns(char const * string,
                                       TFormat const &)
{
//     auto it = directionIterator(string, Input());
    auto it = begin(string);

    // first line is header
    SEQAN_ASSERT(!onMatch(it, TFormat()));

    // skip headers and comment lines
    skipUntilMatch(it, TFormat());

    // now we should be onMatch
    SEQAN_ASSERT(onMatch(it, TFormat()));

    CharString  field1;
    std::string field2;
    double      field3;
    double      field4; // is actually int but cast to double must work, too
    unsigned    field5;
    unsigned    field6;
    unsigned    field7;
    unsigned    field8;
    unsigned    field9;
    unsigned    field10;
    double      field11;
    double      field12;

    readMatch(it, TFormat(), field1, field2, field3, field4, field5, field6,
              field7, field8, field9, field10, field11, field12);

    SEQAN_ASSERT_EQ(field1,          "SHAA004TF");
    SEQAN_ASSERT_EQ(field2,          "sp|P0A916|OMPW_SHIFL");
    SEQAN_ASSERT_EQ(field3,          50.43);
    SEQAN_ASSERT_EQ(field4,          115.0);
    if (string == legacyout)
        SEQAN_ASSERT_EQ(field5,      57u);
    else // legacy blast includes gaps in mismatches
        SEQAN_ASSERT_EQ(field5,      49u);
    SEQAN_ASSERT_EQ(field6,          2u);
    SEQAN_ASSERT_EQ(field7,          389u);
    SEQAN_ASSERT_EQ(field8,          733u);
    SEQAN_ASSERT_EQ(field9,          1u);
    SEQAN_ASSERT_EQ(field10,         107u);
    SEQAN_ASSERT_LEQ(std::abs(field11  - 1e-26), 1e-10);
    SEQAN_ASSERT_LEQ(std::abs(field12 - 108), 1e-3);

    // SEQAN_TRY reading less coluumns than are present
    readMatch(it, TFormat(), field1, field2, field3, field4, field5, field6,
              field7, field8, field9, field10);

    SEQAN_ASSERT_EQ(field1,          "SHAA004TF");
    SEQAN_ASSERT_EQ(field2,          "sp|P0A915|OMPW_ECOLI");
    SEQAN_ASSERT_EQ(field3,          50.43);
    SEQAN_ASSERT_EQ(field4,          115.0);
    if (string == legacyout) // legacy blast includes gaps in mismatches
        SEQAN_ASSERT_EQ(field5,      57u);
    else
        SEQAN_ASSERT_EQ(field5,      49u);
    SEQAN_ASSERT_EQ(field6,          2u);
    SEQAN_ASSERT_EQ(field7,          389u);
    SEQAN_ASSERT_EQ(field8,          733u);
    SEQAN_ASSERT_EQ(field9,          1u);
    SEQAN_ASSERT_EQ(field10,         107u);

    // read remaining matches
    while (onMatch(it, TFormat()))
        readMatch(it, TFormat(), field1); // only one field

    // go to last record with matches
    skipUntilMatch(it, TFormat());

    // goto second (last) match
    skipLine(it);

    // check if exceptions are properly thrown
    CharString exceptComment;
    SEQAN_TRY
    {
        // no strings here to take the strings
        readMatch(it, TFormat(), field3, field4, field5, field6,
                  field7, field8, field9, field10, field11, field12);
    } SEQAN_CATCH (BadLexicalCast const & e)
    {
        exceptComment = e.what();
    }

    SEQAN_ASSERT(startsWith(exceptComment, "Unable to convert"));
    // skip rest of line
    skipLine(it);

    exceptComment = "";
    SEQAN_TRY
    {
        skipUntilMatch(it, TFormat());
    } SEQAN_CATCH (ParseError const & e)
    {
        exceptComment = e.what();
    }

    SEQAN_ASSERT_EQ(exceptComment, "EOF reached without finding Match.");
}

SEQAN_DEFINE_TEST(test_blast_read_tabular_match_customcolumns)
{
    // this tests BlastMatch#readMatch(), BlastMatch#skipMatch() and
    // BlastFormat#skipUntilMatch
    typedef BlastFormat<BlastFormatFile::TABULAR,
                        BlastFormatProgram::BLASTX,
                        BlastFormatGeneration::BLAST_PLUS> TFormat;
    _test_blast_read_tabular_match_columns(out, TFormat());
    // basic match reading should work between plus and legacy
    _test_blast_read_tabular_match_columns(legacyout, TFormat());
}

SEQAN_DEFINE_TEST(test_blast_read_tabular_match_customcolumns_legacy)
{
    // this tests BlastMatch#readMatch(), BlastMatch#skipMatch() and
    // BlastFormat#skipUntilMatch
    typedef BlastFormat<BlastFormatFile::TABULAR,
                        BlastFormatProgram::BLASTX,
                        BlastFormatGeneration::BLAST_LEGACY> TFormat;
    _test_blast_read_tabular_match_columns(out, TFormat());
    // basic match reading should work between plus and legacy
    _test_blast_read_tabular_match_columns(legacyout, TFormat());
}

SEQAN_DEFINE_TEST(test_blast_read_tabular_with_header)
{
    typedef BlastFormat<BlastFormatFile::TABULAR_WITH_HEADER,
                        BlastFormatProgram::BLASTX,
                        BlastFormatGeneration::BLAST_PLUS> TFormat;
    typedef BlastMatchField<BlastFormatGeneration::BLAST_PLUS> TField;

    auto it = begin(out);

    // first line is header
    SEQAN_ASSERT(!onMatch(it, TFormat()));

    CharString qId;
    std::string dbName;
    CharString versionString;
    unsigned long hits = 0;
    StringSet<CharString> fieldStrings;
    CharString fieldStringsConcat;
    String<typename TField::Enum> fieldList;
    StringSet<CharString> otherLines;

    // back on header
    SEQAN_ASSERT(!onMatch(it, TFormat()));

    // all parameters, strict == false
    readHeader(qId, dbName, versionString, hits, fieldStrings, otherLines, it,
               false, TFormat());

    SEQAN_ASSERT_EQ(qId,                "SHAA003TF");
    SEQAN_ASSERT_EQ(dbName,             "/tmp/uniprot_sprot.fasta");
    SEQAN_ASSERT_EQ(versionString,      "BLASTX 2.2.26+");
    SEQAN_ASSERT_EQ(hits,               0u);
    SEQAN_ASSERT_EQ(length(fieldStrings), 0u);
    SEQAN_ASSERT_EQ(length(otherLines), 0u);

    clear(qId, dbName, versionString, hits, fieldStrings, fieldStringsConcat,
          fieldList, otherLines);

    // without hits-parameter, without otherLines parameter
    // strict == false,
    readHeader(qId, dbName, versionString, hits, fieldList, it,
               false, TFormat());

    SEQAN_ASSERT_EQ(qId,                "SHAA003TR");
    SEQAN_ASSERT_EQ(dbName,             "/tmp/uniprot_sprot.fasta");
    SEQAN_ASSERT_EQ(versionString,      "BLASTX 2.2.26+");
    SEQAN_ASSERT_EQ(length(fieldList),  0u);

    clear(qId, dbName, versionString, hits, fieldStrings, fieldStringsConcat,
          fieldList, otherLines);

    // all parameters, strict == true, fields as fields
    readHeader(qId, dbName, versionString, hits, fieldList, otherLines, it,
               true, TFormat());

    SEQAN_ASSERT_EQ(qId,                "SHAA004TF");
    SEQAN_ASSERT_EQ(dbName,             "/tmp/uniprot_sprot.fasta");
    SEQAN_ASSERT_EQ(versionString,      "BLASTX 2.2.26+");
    SEQAN_ASSERT_EQ(hits,               17u);
    SEQAN_ASSERT_EQ(length(fieldList),  1u);
    SEQAN_ASSERT_EQ(fieldList[0],       TField::Enum::STD);
    SEQAN_ASSERT_EQ(length(otherLines), 0u);

    clear(qId, dbName, versionString, hits, fieldStrings, fieldStringsConcat,
          fieldList, otherLines);

    while (onMatch(it, TFormat()))
        skipMatch(it, TFormat());

    // without otherlines parameter, strict == true, fields as strings
    readHeader(qId, dbName, versionString, hits, fieldStrings, it,
               true, TFormat());

    joinStringSet(fieldStringsConcat, fieldStrings, ", ");

    SEQAN_ASSERT_EQ(qId,                "SHAA004TR");
    SEQAN_ASSERT_EQ(dbName,             "/tmp/uniprot_sprot.fasta");
    SEQAN_ASSERT_EQ(versionString,      "BLASTX 2.2.26+");
    SEQAN_ASSERT_EQ(hits,               2u);
    SEQAN_ASSERT_EQ(fieldStringsConcat, TField::columnLabels[0]);

    clear(qId, dbName, versionString, hits, fieldStrings, fieldStringsConcat,
          fieldList, otherLines);

    // check if exceptions are properly thrown
    CharString exceptComment;
    SEQAN_TRY
    {
        // all parameters, strict == true
        // artifical type Datacase instead of Database should trigger exception
        readHeader(qId, dbName, versionString, hits, fieldStrings, otherLines, it,
                   true, TFormat());
    } SEQAN_CATCH (RecoverableParseError const & e)
    {
        exceptComment = e.what();
    }

    SEQAN_ASSERT_EQ(exceptComment, "Header did not meet strict requirements.");

    SEQAN_ASSERT_EQ(qId,                "SHAA005TR");
    SEQAN_ASSERT_EQ(dbName,             ""); // couldnt be retrieved
    SEQAN_ASSERT_EQ(versionString,      "BLASTX 2.2.26+");
    SEQAN_ASSERT_EQ(hits,               0u);
    SEQAN_ASSERT_EQ(length(fieldStrings), 0u);
    SEQAN_ASSERT_EQ(length(otherLines), 1u);
    SEQAN_ASSERT_EQ(otherLines[0],      "# Datacase: /tmp/uniprot_sprot.fasta");
}


// SEQAN_DEFINE_TEST(test_blast_read_tabular_basics_header)
// {
//     typedef BlastFormat<BlastFormatFile::TABULAR_WITH_HEADER,
//                         BlastFormatProgram::BLASTX,
//                         BlastFormatGeneration::BLAST_PLUS> TFormat;
//     _test_blast_read_tabular_basics_match(TFormat());
// }

