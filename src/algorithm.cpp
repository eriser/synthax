#include "algorithm.h"

/*
    ============
    construction
    ============
*/

algorithm::algorithm(node* r, std::string o) :
    id(-1), origin(o), height(-1), fitness(-1),
    minimum((-1) * std::numeric_limits<float>::infinity()), maximum(std::numeric_limits<float>::infinity()),
    traced(false), prepared_to_render(false),
    render_root(new SilenceNode()), root(r), all_nodes(0), all_mutatable_params(0)
{
}

algorithm::~algorithm() {
    if (!prepared_to_render) {
        delete root;
    }
    delete render_root;
}

algorithm* algorithm::getCopy(std::string neworigin) {
    algorithm* copy = new algorithm(root->get_copy(), neworigin);
    return copy;
}

/*
    ===========
    examination
    ===========
*/

void algorithm::evaluateBlockPerformance(unsigned firstFrameNumber, unsigned numSamples, float* sampleTimes, unsigned numConstantVariables, float* constantVariables, float* buffer) {
    render_root->evaluateBlockPerformance(firstFrameNumber, numSamples, sampleTimes, numConstantVariables, constantVariables, buffer);
}


std::string algorithm::to_string(unsigned precision) {
    std::stringstream ss;
    ss.precision(precision);
    root->to_string(ss);
    return ss.str();
}

node* algorithm::get_root() {
    return root;
}

bool algorithm::equals(algorithm* other, unsigned precision) {
    return to_string(precision).compare(other->toString(precision)) == 0;
}

node* algorithm::get_random_network_node(random* r) {
    assert(traced = true);
    return all_nodes[r->random(allNodes.size())];
}

std::vector<param*>* algorithm::get_all_mutatable_params() {
    assert(traced = true);
    return &all_mutatable_params;
}

/*
    =======
    helpers
    =======
*/

void algorithm::trace() {
    all_nodes.clear();
    all_mutatable_params.clear();
    root->trace(&all_nodes, &all_mutatable_params, NULL, &height, 0);
    traced = true;
}

// render_root = silence and root = realroot whenever prepared_to_render is false
// render_root = realroot and root = realroot whenever prepared_to_render is true
void algorithm::prepare_to_render(float sr, unsigned block_size, unsigned max_frame_number, float max_frame_start_time) {
    done_rendering();
    if (!prepared_to_render) {
        delete render_root;
    }
    root->set_render_info(sr, block_size, max_frame_number, max_frame_start_time);
    render_root = root;
    prepared_to_render = true;
    update_mutated_params();
}

// only changed the params
void algorithm::update_mutated_params() {
    assert(prepared_to_render);
    root->update_mutated_params();
    minimum = root->minimum;
    maximum = root->maximum;
}

void algorithm::done_rendering() {
    if (prepared_to_render) {
        root->done_rendering();
        minimum = (-1) * std::numeric_limits<float>::infinity();
        maximum = std::numeric_limits<float>::infinity();
        render_root = new SilenceNode();
        prepared_to_render = false;
    }
}

/*
    this method replaces the subtree rooted at node old with node new's
*/
void algorithm::replace_subtree(node* old, GPNode* nu) {
    // handle root case
    if (old == root) {
        root = nu;
    }
    else {
        // replace parent-child links
        bool replaced_link = false;
        for (unsigned i = 0; i < old->parent->arity; i++) {
            if (old->parent->descendants[i] == old) {
                old->parent->descendants[i] = nu;
                replaced_link = true;
            }
        }
        if (!replaced_link)
            std::cerr << "Bad parent-child links detected during subtree replacement." << std::endl;
    }
    /*
    // assign nu parent pointer
    nu->parent = old->parent;
    */

    traced = false;
}

void algorithm::ephemeral_random(random* r) {
    root->ephemeral_random(r);
}

// method to compare networks by identification
bool compare_algorithms_by_id(algorithm* one, algorithm* two) {
	return one->id < two->id;
}