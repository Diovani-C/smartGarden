import { writable } from 'svelte/store';
import { Record } from 'immutable';

const InitialState = Record<State>({ from: '', to: '' });

function createGlobalState() {
	const { subscribe, update } = writable(InitialState());

	return {
		subscribe,
		updateFrom: (from: string) => update((lastState) => lastState.set('from', from)),
		updateTo: (to: string) => update((lastState) => lastState.set('to', to))
	};
}

export default createGlobalState();
